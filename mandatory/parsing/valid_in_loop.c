/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_in_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:24:22 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/26 20:20:49 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_char(char c)
{
	return (c != '"' && c != '\'' && c != '\0' 
	&& c != '$' && c != ' ' && c != '>' && c != '<');
}

int	valid_token(t_tokens *token, char char_input)
{
	return (char_input != ' ' && char_input != '\0' 
			&& char_input != '|' && token->errnum == DEFAULT);
}

void	append_char(char **input, char **result)
{
	*result = concat_str(*result, ft_substr(*input, 0, 1));
	(*input)++;
}

int	valid_redir(char c)
{
	return (c == '>' || c == '<');
}
