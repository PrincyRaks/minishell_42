/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:07:28 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/16 11:27:49 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal_status(int status)
{
	if (WTERMSIG(status) == SIGINT)
	{
		set_status(130);
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		set_status(131);
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
}

static void	wait_all_pids(pid_t *pids, int count)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				set_status(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				handle_signal_status(status);
		}
		i++;
	}
	set_signals_interactive();
}

void	execute_pipeline(t_tokens *tokens)
{
	int		prev_fd;
	pid_t	pids[1024];
	int		pid_index;

	set_signals_pipe();
	prev_fd = -1;
	pid_index = 0;
	while (tokens)
	{
		execute_command(tokens, &prev_fd, pids, &pid_index);
		tokens = tokens->next;
	}
	if (prev_fd != -1)
	{
		close(prev_fd);
	}
	wait_all_pids(pids, pid_index);
}
