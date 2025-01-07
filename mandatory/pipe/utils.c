/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:12:14 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/07 16:59:57 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*get_prev_token(t_tokens *head, t_tokens *current)
{
	t_tokens	*prev;
	t_tokens	*temp;

	prev = NULL;
	temp = head;
	if (current == head)
		return (NULL);
	while (temp && temp != current)
	{
		prev = temp;
		temp = temp->next;
	}
	return (prev);
}

void	setup_child_process(t_tokens *tokens, t_tokens *current, int prev_fd,
		int *pipe_fd)
{
	set_signals_noninteractive();
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDOUT_FILENO);
		close(prev_fd);
	}
	if (current != tokens)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	execute_single_command(current);
}

int	check_command(t_tokens *current)
{
	if (!current->token_cmd || (!is_builtin(current->token_cmd->cmd_str)
		&& !find_executable(current->token_cmd->cmd_str)))
	{
		if (current->token_cmd != NULL && current->token_cmd->cmd_str != NULL 
			&& (current->token_cmd->cmd_str[0] == '/' || current->token_cmd->cmd_str[0] == '.'))
		{
			if (access(current->token_cmd->cmd_str, F_OK) != 0)
			{
				ft_putstr_fd(" : ", 2);
				ft_putstr_fd(current->token_cmd->cmd_str, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
			}
			else if (access(current->token_cmd->cmd_str, X_OK) != 0)
			{
				ft_putstr_fd(" : ", 2);
				ft_putstr_fd(current->token_cmd->cmd_str, 2);
				ft_putstr_fd(": Permission denied\n", 2);
			}
		}
		else
		{
			ft_putstr_fd(current->token_cmd->cmd_str, 2);
			ft_putstr_fd(" : command not found\n", 2);
		}
		return (0);
	}
	return (1);
}

void	handle_pipe_fds(t_tokens *tokens, t_tokens *current, int *prev_fd,
		int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current != tokens)
	{
		close(pipe_fd[0]);
		*prev_fd = pipe_fd[1];
	}
}

void	execute_command(t_tokens *tokens, t_tokens *current, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (current != tokens && pipe(pipe_fd) == -1)
	{
		set_signals_interactive();
		exit_perror("pipe");
	}
	if (!check_command(current))
		return ;
	pid = fork();
	if (pid == -1)
		exit_perror("fork");
	if (pid == 0)
		setup_child_process(tokens, current, *prev_fd, pipe_fd);
	handle_pipe_fds(tokens, current, prev_fd, pipe_fd);
}
