/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_specialchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 17:58:28 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/17 13:51:45 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_inquotes(t_tokens *token)
{
	t_arg	*end_arg;

	if (!token->token_cmd)
		token->token_cmd = new_cmd();
	if (token->token_cmd && !token->token_cmd->cmd_str)
	{
		token->token_cmd->operand = INQUOTES;
		return ;
	}
	end_arg = last_arg(token->token_arg);
	if (!end_arg)
	{
		token->token_arg = new_arg();
		end_arg = token->token_arg;
	}
	if (end_arg && !end_arg->arg_str)
		end_arg->operand = INQUOTES;
	if (end_arg && end_arg->operand == INQUOTES && end_arg->arg_str)
	{
		end_arg->next_arg = new_arg();
		end_arg->next_arg->operand = INQUOTES;
	}
}

char	*handle_onequotes(char **qts, char **result, t_tokens *token)
{
	char	*trim;

	trim = remove_onequotes(qts);
	if (!trim)
	{
		free(*result);
		token->errnum = UNQUOTES;
		return (NULL);
	}
	*result = concat_str(*result, trim);
	set_inquotes(token);
	return (*result);
}

char	*handle_doubquotes(char **qts, char **result, t_tokens *token,
		int is_expand)
{
	char	*trim;

	trim = remove_doubquotes(qts, is_expand);
	if (!trim)
	{
		free(*result);
		token->errnum = UNQUOTES;
		return (NULL);
	}
	*result = concat_str(*result, trim);
	set_inquotes(token);
	return (*result);
}

void	handle_var(char **input, char **res, t_tokens *token, int *mode)
{
	char	*expand;

	if (*(*input + 1) == '"' || *(*input + 1) == '\'')
	{
		(*input)++;
		return ;
	}
	if (ft_isdigit(*(*input + 1)))
	{
		(*input) += 2;
		return ;
	}
	expand = handle_dollar(input);
	if (!expand && (!ft_isspace(**input) || **input == '\0' || **input == '|'))
		set_void_operand(token, *mode);
	if (expand != NULL)
		*res = concat_str(*res, expand);
	set_option3(mode, token, expand);
}
