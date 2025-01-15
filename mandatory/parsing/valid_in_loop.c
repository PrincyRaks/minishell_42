/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_in_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:24:22 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/09 16:10:34 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_store(char c)
{
	return (c != ' ' && c != '\0' && c != '|');
}

int	valid_arguments(t_tokens *node, int mode_add, char *str_parsing)
{
	return (node->token_cmd != NULL && mode_add == 2 && str_parsing != NULL);
}

int	valid_char(char c)
{
	return (c != '"' && c != '\'' && c != '\0' && c != '$' && c != ' '
		&& c != '>' && c != '<');
}

int	valid_token(t_tokens *token, char char_input)
{
	return (char_input != ' ' && char_input != '\0' && char_input != '|'
		&& token->errnum == DEFAULT);
}

int	valid_redir(char c)
{
	return (c == '>' || c == '<');
}
