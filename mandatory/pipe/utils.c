/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:12:14 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/15 16:36:00 by mrazanad         ###   ########.fr       */
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
	(void)tokens;
	set_signals_noninteractive();
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			perror("dup2 prev_fd");
		close(prev_fd);
	}
	if (current->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2 pipe_fd");
		close(pipe_fd[1]);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (current->token_cmd && current->token_cmd->cmd_str)
	{
		if (!check_command(current) && count_token(tokens) == 1)
			clean_up_exit(get_status());
	}
	execute_single_command(current);
}

void	handle_pipe_fds(t_tokens *tokens, t_tokens *current, int *prev_fd,
		int *pipe_fd)
{
	(void)tokens;
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
	{
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
		*prev_fd = -1;
	}
}

void	exit_perror(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
