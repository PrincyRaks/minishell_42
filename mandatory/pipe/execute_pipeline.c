/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:07:28 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/17 14:30:21 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(t_tokens *tokens)
{
	int		pipe_fd[2];
	int		prev_fd = -1;
	pid_t	pid;
	int		status;

	while (tokens)
	{
		if (tokens->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (tokens->next)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			if (tokens->next)
				close(pipe_fd[1]);
			execute_single_command(tokens);
			exit(127);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (tokens->next)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
		}
		tokens = tokens->next;
	}
	while (wait(&status) > 0)
		;
}
