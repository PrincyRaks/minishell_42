/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:12:14 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/13 13:34:19 by mrazanad         ###   ########.fr       */
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
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (current->token_cmd && current->token_cmd->cmd_str)
		check_command(current);
	execute_single_command(current);
}

int	check_command(t_tokens *current)
{
	t_tokens	*temp;
	t_tokens	*cmd_token;
	struct stat	path_stat;

	temp = current;
	cmd_token = NULL;
	while (temp)
	{
		if (temp->token_cmd && temp->token_cmd->cmd_str)
		{
			cmd_token = temp;
			break ;
		}
		temp = temp->next;
	}
	if (!cmd_token || !cmd_token->token_cmd->cmd_str)
		return (0);
	if (is_only_dots(cmd_token->token_cmd->cmd_str)
		|| (ft_strcmp(cmd_token->token_cmd->cmd_str, "..") == 0))
	{
		if (ft_strcmp(cmd_token->token_cmd->cmd_str, ".") == 0)
		{
			handle_one_dot(cmd_token->token_cmd->cmd_str, 0, 0);
			return (0);
		}
		ft_putstr_fd(cmd_token->token_cmd->cmd_str, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	if (stat(cmd_token->token_cmd->cmd_str, &path_stat) == 0
		&& S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(cmd_token->token_cmd->cmd_str, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (0);
	}
	if (!is_builtin(cmd_token->token_cmd->cmd_str)
		&& !find_executable(cmd_token->token_cmd->cmd_str))
	{
		if (cmd_token->token_cmd->cmd_str[0] == '/'
			|| cmd_token->token_cmd->cmd_str[0] == '.')
		{
			if (access(cmd_token->token_cmd->cmd_str, F_OK) != 0)
			{
				ft_putstr_fd(cmd_token->token_cmd->cmd_str, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
			}
			else if (access(cmd_token->token_cmd->cmd_str, X_OK) != 0)
			{
				ft_putstr_fd(cmd_token->token_cmd->cmd_str, 2);
				ft_putstr_fd(": Permission denied\n", 2);
			}
		}
		else
		{
			ft_putstr_fd(cmd_token->token_cmd->cmd_str, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		return (0);
	}
	return (1);
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

void	execute_command(t_tokens *tokens, t_tokens *current, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int status;

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
	pid = fork();
	if (pid == -1)
		exit_perror("fork");
	if (pid == 0)
	{
		setup_child_process(tokens, current, *prev_fd, pipe_fd);
	}
	else if (pid > 0)
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
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}
