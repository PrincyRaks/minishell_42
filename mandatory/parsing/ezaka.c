/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ezaka.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:23:36 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/09 22:13:26 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void add_parse_token(t_tokens *token, char *parse_input, int mode_arg)
{
    // mode_arg = 0->new cmd
    // mode_arg = 1-> set value cmd
    // mode_arg = 2-> set value arg
    // mode_arg = 3-> new arg
	if (token->token_cmd != NULL && (mode_arg == 1 || mode_arg == 2))
	{
        if (mode_arg == 1)
            token->token_arg->arg_str = parse_input
        else
		    addback_arg(&node_token->token_arg, parse_input);
		return ;
	}
    if (!mode_arg)
        token->token_cmd = new_cmd();
    token->token_cmd->cmd_str = parse_input;
}

static char	*handle_onequotes(char **qts, char **result, t_tokens *token)
{
	char	*trim;

	trim = remove_onequotes(qts);
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

static char	*handle_doubquotes(char **qts, char	**result)
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

// ovaina tokens ny argument anty hihihi !
t_tokens	*parse_input(t_tokens *token, char **input)
{
	char	*result;

    if (!token)
        return (NULL);    
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
