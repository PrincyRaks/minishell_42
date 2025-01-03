/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:17:21 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/24 17:30:34 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredocvar(char **input, char *result)
{
	size_t	len_res;

	len_res = ft_strlen(result);
	if (*(*input + 1) == '"' || *(*input + 1) == '\'')
	{
		len_res = count_dollar(result);
		if (len_res > 0 && *(*input - 1) == '$')
		{
			free(result);
			result = dupnb_dollar(len_res + 1);
		}
		(*input)++;
	}
	if (**input != '"' && **input != '\'')
	{
		result = concat_str(result, ft_substr(*input, 0, 1));
		(*input)++;
	}
	return (result);
}

static void	set_notop_element(t_tokens *token, int mode, char *res)
{
	size_t	len_res;
	t_arg	*end_arg;

	len_res = ft_strlen(res);
	end_arg = last_arg(token->token_arg);
	printf("mode:%d len: %zu\n", mode, len_res);
	if (mode == 1 && token->token_cmd->operand == VOIDTOKEN && len_res > 0)
		token->token_cmd->operand = NOTOP;
	else if (token->token_arg != NULL && mode == 2 && end_arg->operand == VOIDTOKEN 
		&& len_res > 0)
		end_arg->operand = NOTOP;
}

char	**parse_specific(char  **str, char **res, t_tokens *token, int is_expand)
{
	if (**str == '"' && !handle_doubquotes(str, res, token, is_expand))
		return (NULL);
	if (**str == '\'' && !handle_onequotes(str, res, token))
		return (NULL);
	if (valid_char(**str))
		append_char(str, res);
	return (res);
}

char	*parse_input(t_tokens *token, char **input, int *mode)
{
	char	*result;
	int		exp;

	exp = 1;
	result = ft_calloc(1, sizeof(char));
	while(valid_token(token, **input))
	{
		if ((**input == '"' || **input == '\'' || valid_char(**input))
			&& !parse_specific(input, &result, token, exp))
			return(NULL);
		if (**input == '$')
		{
			if (exp)
				handle_var(input, &result, token, mode);
			else if (!exp && **input == '$')
				result = expand_heredocvar(input, result);
		}
		if ((ft_strlen(result) > 0 || *mode == 4) && valid_redir(**input))
			return (result);
		if (valid_redir(**input) && !handle_flow(token, input, mode, &exp))
			return (free(result), NULL);
	}
	set_notop_element(token, *mode, result);
	return (result);
}
