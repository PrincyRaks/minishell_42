/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 09:26:56 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/22 11:31:01 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_errnum(t_errnum numerr)
{
	if (numerr == DEFAULT)
		return ;
	else if (numerr == ERRMALLOC)
		ft_putstr_fd("Error: allocation of memory\n", 2);
    else if (numerr == UNQUOTES)
        ft_putstr_fd("Error: unclosed quotes\n", 2);
	else if (numerr == ERRFLOW)
		ft_putstr_fd("Error: syntax error near unexpected token `redirection'\n", 2);
	else if (numerr == ERRPIPE)
		ft_putstr_fd("Error: syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd("Error: ambiguous redirect\n", 2);
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
