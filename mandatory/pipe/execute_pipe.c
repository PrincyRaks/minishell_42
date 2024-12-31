/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:07:28 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/31 11:08:13 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static t_tokens *get_prev_token(t_tokens *head, t_tokens *current)
{
	t_tokens *prev = NULL;
	t_tokens *temp = head;

	if (current == head)
		return NULL;

	while (temp && temp != current)
	{
		prev = temp;
		temp = temp->next;
	}
	return prev;
}

static void	setup_child_process(t_tokens *tokens, t_tokens *current,
		int prev_fd, int *pipe_fd)
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

static int	check_command(t_tokens *current)
{
	if (!current->token_cmd || !current->token_cmd->cmd_str
		|| (!is_builtin(current->token_cmd->cmd_str)
		&& !find_executable(current->token_cmd->cmd_str)))
	{
		ft_putstr_fd(current->token_cmd->cmd_str, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	return (1);
}

static void	handle_pipe_fds(t_tokens *tokens, t_tokens *current,
		int *prev_fd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current != tokens)
	{
		close(pipe_fd[0]);
		*prev_fd = pipe_fd[1];
	}
}

static void	execute_command(t_tokens *tokens, t_tokens *current, int *prev_fd)
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

void	execute_pipeline(t_tokens *tokens)
{
	int			prev_fd;
	t_tokens	*current;
	t_tokens	*last;

	set_signals_pipe();
	last = tokens;
	while (last->next)
		last = last->next;
	if (!check_command(last))
	{
		set_signals_interactive();
		return ;
	}
	prev_fd = -1;
	current = last;
	while (current)
	{
		execute_command(tokens, current, &prev_fd);
		current = get_prev_token(tokens, current);
	}
	while (wait(NULL) > 0)
		;
	set_signals_interactive();
}
