/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ezaka.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:23:36 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/10 14:54:28 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_parse_token(t_tokens *token, char *parse_input, int mode_add)
{
	// mode_add = 0->new cmd
	// mode_add = 1-> set value cmd
// miova 2 ny mode rah tapitra tanteraka le boucle ao;
	// mode_add = 2-> set value arg
	// mode_add = 3-> new arg
	if (token->token_cmd != NULL && (mode_add == 2 || mode_add == 3))
	{
		if (mode_add == 2)
			token->token_arg->arg_str = parse_input;
		else
			addback_arg(&node_token->token_arg, parse_input);
		return ;
	}
	if (!mode_add)
	{
		token->token_cmd = new_cmd();
		mode_add = 1;
	}
	token->token_cmd->cmd_str = parse_input;
}

static t_tokens	*handle_onequotes(char **qts, char **result, t_tokens *token, int *option)
{
	char	*trim;

	trim = remove_onequotes(qts);
	// if error unclosed quotes
	if (!trim)
	{
		free(trim);
		free(*result);
		if (!token->token_arg)
			token->token_cmd->errnum = UNQUOTES;
		else
			last_arg(token->token_arg)->errnum = UNQUOTES;
		return (token);
	}
	// eto bola ovaina !
	*result = concat_str(*result, trim);
	add_parse_token();
	return (token);
}

static char	*handle_doubquotes(char **qts, char **result)
{
	char	*trim;

	trim = remove_doubquotes(qts);
	// if error unclosed quotes
	if (!trim)
	{
		free(trim);
		free(*result);
		return (NULL);
	}
	*result = concat_str(*result, trim);
	return (*result);
}

static char	*handle_var(char **input, char **result, t_tokens *token)
{
	char	*expand;

	if (*(*input + 1) == '"' || *(*input + 1) == '\'')
		(*input)++;
	else
	{
		expand = handle_dollar(input);
		// !!!eto le mi-verifier oe $variable ve NULL !!!!
		// if (strlen(*result) == 0 && expand == NULL) de NULL le argument zay
		if (expand != NULL)
			*result = concat_str(*result, expand);
	}
	return (*result);
}

// Pour 1 tokens ato izy no mi-ajouter cmd sy arguments drai
t_tokens	*parse_input(t_tokens *token, char **input)
{
	char	*result;

	if (!token)
		return (NULL);
	mode_add = 0;
	result = ft_calloc(1, sizeof(char));
	while (**input != ' ' && **input != '\0' && **input != '|')
	{
		if (**input == '"' && handle_doubquotes(input, &result, token) == NULL)
			return (NULL);
		if (**input == '\'' && handle_onequotes(input, &result, token) == NULL)
			return (NULL);
		if (**input != '"' && **input != '\'' && **input != '\0'
			&& **input != ' ' && **input != '$')
		{
			result = concat_str(result, ft_substr(*input, 0, 1));
			(*input)++;
		}
		if (**input == '$' && handle_var(input, &result, token) == NULL)
			return (NULL);
	}
	return (result);
}

int	is_unclosequote(t_tokens *token)
{
	t_arg	*arg_cmd;

	if (token->token_cmd && token->token_cmd->errnum == UNQUOTES)
		return (1);
	arg_cmd = token->token_arg;
	while (arg_cmd != NULL)
	{
		if (arg_cmd->errnum == UNQUOTES)
			return (1);
		arg_cmd = arg_cmd->next_arg;
	}
	return (0);
}

t_tokens	*store_parse_token(t_tokens *token, char **input)
{
	char	*result;
	int		mode_add;

	if(!token)
		return (NULL);
	mode_add = 0;
	result = ft_calloc(0, sizeof(char));
	
	// while (**input != '\0' && **input != '|')
	// {
	// 	/* code */
	// }
	
		while (**input != ' ' && **input != '\0' && **input != '|')
		{
			if (**input == '"' && is_unclosequote(handle_onequotes(input, &result, token, mode_add)))
				return (token);
			if (**input != '"' && **input != '\'' && **input != '\0'
				&& **input != ' ' && **input != '$')
			{
				add_parse_token(token, concat_str(result, ft_substr(*input, 0, 1)), &mode_add);
				(*input)++;
			}
		}
		if (mode_add == 2)
			mode_add = 3;
		add_parse_token(token, &result, mode_add);
		if (mode_add == 1)
			mode_add = 2;
}
