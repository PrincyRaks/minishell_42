/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:07:28 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/26 13:10:42 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(t_tokens *tokens)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;
	char	*executable;
	char	**argv;

	prev_fd = -1;
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
			executable = find_executable(tokens->token_cmd->cmd_str);
			if (!executable)
			{
				printf("command not found: %s\n",
					tokens->token_cmd->cmd_str);
				exit(EXIT_FAILURE);
			}
			argv = array_tokens(tokens);
			execve(executable, argv, get_tabenv());
			perror("execve");
			exit(EXIT_FAILURE);
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
			waitpid(pid, NULL, 0);
		}
		tokens = tokens->next;
	}
}
