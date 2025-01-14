/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:58:56 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/14 06:49:02 by mrazanad         ###   ########.fr       */
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

static void	handle_parent_signals(pid_t pid, int status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	set_signals_interactive();
	if (status & 0x7F)
	{
		if ((status & 0x7F) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if ((status & 0x7F) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
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

void	execute_command(t_tokens *tokens, t_tokens *current, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	setup_the_pipe(*prev_fd, pipe_fd, current);
	pid = fork();
	if (pid == -1)
		exit_perror("fork");
	if (pid == 0)
		setup_child_process(tokens, current, *prev_fd, pipe_fd);
	else if (pid > 0)
		handle_parent_signals(pid, status);
	handle_pipe_cleanup(prev_fd, pipe_fd, current);
}
