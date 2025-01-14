/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:54:31 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/14 06:48:50 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens	*find_cmd_token(t_tokens *current)
{
	t_tokens	*temp;

	temp = current;
	while (temp)
	{
		if (temp->token_cmd && temp->token_cmd->cmd_str)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static int	handle_dots_check(t_tokens *cmd_token)
{
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
	return (1);
}

static int	handle_directory_check(t_tokens *cmd_token)
{
	struct stat	path_stat;

	if (stat(cmd_token->token_cmd->cmd_str, &path_stat) == 0
		&& S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(cmd_token->token_cmd->cmd_str, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (0);
	}
	return (1);
}

static int	handle_command_errors(t_tokens *cmd_token)
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

int	check_command(t_tokens *current)
{
	t_tokens	*cmd_token;

	cmd_token = find_cmd_token(current);
	if (!cmd_token || !cmd_token->token_cmd->cmd_str)
		return (0);
	if (!handle_dots_check(cmd_token))
		return (0);
	if (!handle_directory_check(cmd_token))
		return (0);
	if (!is_builtin(cmd_token->token_cmd->cmd_str)
		&& !find_executable(cmd_token->token_cmd->cmd_str))
		return (handle_command_errors(cmd_token));
	return (1);
}
