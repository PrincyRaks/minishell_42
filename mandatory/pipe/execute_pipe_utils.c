/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+         +:+     */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:33:33 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/31 09:41:05 by mrazanad         ###   ########.fr       */
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
	int	last_status;

	last_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	}
	if (last_status != 0)
		exit(last_status);
}

void	handle_child(int prev_fd, int pipe_fd[2], t_tokens *tokens)
{
	setup_pipe(prev_fd, pipe_fd, tokens);
	if (tokens->token_cmd == NULL || tokens->token_cmd->cmd_str == NULL)
		exit(0);
	if (apply_redirection(tokens) == -1)
		exit(1);
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
