/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:58:56 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/16 10:32:17 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_the_pipe(int prev_fd, int pipe_fd[2], t_tokens *current)
{
	(void)prev_fd;
	if (current->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			set_signals_interactive();
			exit_perror("pipe");
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
}

static void	handle_pipe_cleanup(int *prev_fd, int *pipe_fd, t_tokens *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

void	execute_command(t_tokens *current, int *prev_fd,
		pid_t *pids, int *index)
{
	int		pipe_fd[2];
	pid_t	pid;

	setup_the_pipe(*prev_fd, pipe_fd, current);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		clean_up_exit(EXIT_FAILURE);
	}
	if (pid == 0)
		setup_child_process(current, current, *prev_fd, pipe_fd);
	else if (pid > 0)
	{
		pids[*index] = pid;
		(*index)++;
	}
	handle_pipe_cleanup(prev_fd, pipe_fd, current);
}
