/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:33:33 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/24 10:43:58 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_pipe(int prev_fd, int pipe_fd[2], t_tokens *tokens)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (tokens->next)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
	}
}

void	wait_for_children(void)
{
	int	status;

	while (wait(&status) > 0)
		;
}

void	handle_child(int prev_fd, int pipe_fd[2], t_tokens *tokens)
{
	setup_pipe(prev_fd, pipe_fd, tokens);
	if (apply_redirection(tokens) == -1)
	{
		perror("apply_redirection");
		exit(1);
	}
	if (is_builtin(tokens->token_cmd->cmd_str))
	{
		execute_builtin(tokens, is_builtin(tokens->token_cmd->cmd_str));
		exit(0);
	}
	else
		execute_single_command(tokens);
	exit(127);
}

int	handle_parent(int prev_fd, int pipe_fd[2], t_tokens *tokens)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (tokens->next)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}

void	exit_perror(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
