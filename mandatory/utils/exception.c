/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:26:56 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/15 10:32:36 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_errnum(t_errnum numerr)
{
	int	status;

	status = 2;
	if (numerr == DEFAULT)
		return ;
	else if (numerr == ERRMALLOC)
		ft_putstr_fd("Error: allocation of memory\n", 2);
	else if (numerr == UNQUOTES)
		ft_putstr_fd("Error: unclosed quotes\n", 2);
	else if (numerr == ERRFLOW)
	{
		ft_putstr_fd("Error: syntax error near unexpected ", 2);
		ft_putendl_fd("token `redirection'", 2);
	}
	else if (numerr == ERRPIPE)
		ft_putstr_fd("Error: syntax error near unexpected token `|'\n", 2);
	else if (numerr == AMBIGUOUS)
	{
		ft_putstr_fd("Error: ambiguous redirect\n", 2);
		status = 1;
	}
	set_status(status);
}

t_errnum	check_errnum(t_tokens *token)
{
	t_arg	*arg_cmd;

	if (token->token_cmd && token->token_cmd->errnum != DEFAULT)
		return (token->token_cmd->errnum);
	arg_cmd = token->token_arg;
	while (arg_cmd != NULL)
	{
		if (arg_cmd->errnum != DEFAULT)
			return (arg_cmd->errnum);
		arg_cmd = arg_cmd->next_arg;
	}
	return (DEFAULT);
}

void	print_error_access(t_flow *redir)
{
	struct stat	st;

	if (stat(redir->word, &st) != 0)
	{
		ft_putstr_fd(" : No such file or directory\n", 2);
		set_status(1);
	}
	else if (((redir->operand == OUTPUT || redir->operand == APPEND)
			&& access(redir->word, W_OK) != 0) || (redir->operand == INPUT
			&& access(redir->word, R_OK) != 0))
	{
		ft_putstr_fd(redir->word, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

void	print_error_directory(char *str)
{
	if (access(str, F_OK) != 0)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		set_status(127);
	}
	else if (access(str, X_OK) != 0)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		set_status(126);
	}
}
