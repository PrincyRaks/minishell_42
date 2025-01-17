/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_in_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:24:22 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/17 13:43:44 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_store(char c)
{
	return (!ft_isspace(c) && c != '\0' && c != '|');
}

int	valid_arguments(t_tokens *node, int mode_add, char *str_parsing)
{
	return (node->token_cmd != NULL && mode_add == 2 && str_parsing != NULL);
}

int	valid_char(char c)
{
	return (c != '"' && c != '\'' && c != '\0' && c != '$' && !ft_isspace(c)
		&& c != '>' && c != '<' && c != '|');
}

int	valid_token(t_tokens *token, char char_input)
{
	return (!ft_isspace(char_input) && char_input != '\0' && char_input != '|'
		&& (token->errnum == DEFAULT || token->errnum == AMBIGUOUS));
}

int	valid_redir(char c)
{
	return (c == '>' || c == '<');
}
