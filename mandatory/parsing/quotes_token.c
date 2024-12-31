/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:17:21 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/30 22:01:48 by mrazanad         ###   ########.fr       */
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

// static void	setfull_element(t_tokens *token, int mode, char *res)
// {
// 	size_t	len_res;
// 	t_arg	*end_arg;

// 	len_res = ft_strlen(res);
// 	end_arg = last_arg(token->token_arg);
// 	//printf("mode:%d operand: %d len: %zu\n", mode, token->token_cmd->operand, len_res);
// 	if (mode == 1 && token->token_cmd->operand == VOIDTOKEN && len_res > 0)
// 		token->token_cmd->operand = NOTOP;
// 	else if (token->token_arg != NULL && mode == 2 && end_arg->operand == VOIDTOKEN 
// 			&& len_res > 0)
// 		end_arg->operand = NOTOP;
// }

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
	int		is_expand;

	is_expand = 1;
	result = ft_calloc(1, sizeof(char));
	while(valid_token(token, **input))
	{
		if (**input == '"' || **input == '\'')
		{
			if (!parse_specific(input, &result, token, is_expand))
			{
				if (*mode == 4)
				{
					ft_putstr_fd(" : No such file or directory\n", 2);
					token->errnum = ERRFLOW;
				}
				return (NULL);
			}
		}
		else if (**input == '$')
		{
			if (is_expand)
				handle_var(input, &result, token, mode);
			else if (!is_expand && **input == '$')
				result = expand_heredocvar(input, result);
		}
		else if (valid_redir(**input))
		{
			if (!handle_flow(token, input, mode, &is_expand))
				return (free(result), NULL);
		}
		else
		{
			append_char(input, &result);
		}
	}
	if (*mode == 4 && (!result || !*result))
	{
		ft_putstr_fd(" : No such file or directory\n", 2);
		token->errnum = DEFAULT;
	}
	return (result);
}
