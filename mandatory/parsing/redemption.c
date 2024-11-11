/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redemption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:40:52 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/11 12:15:18 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quotes(char **start_quotes)
{
	char *result;
	char *trim;
    int is_close;
	char	quote;


	result = ft_calloc(1, sizeof(char));
    is_close = 0;
	while (**start_quotes != ' ' && is_close == 2)
	{
		if (**start_quotes != '"' && **start_quotes != '\''
			&& **start_quotes != '\0')
		{
			trim = ft_substr(*start_quotes, 0, 1);
			result = ft_strjoin(result, trim);
			free(trim);
			(*start_quotes)++;
		}
		else if (is_close == 1 && (**start_quotes != quote || **start_quotes == ' '))
		{
			//unclosed quotes 
			return (NULL);
		}
		else if (**start_quotes == '"')
		{
			trim = remove_doubquotes(start_quotes);
			if (!trim)
			{
				free(trim);
				free(result);
				return (NULL);
			}
			result = ft_strjoin(result, trim);
			free(trim);
			quote = '"';
		}
		else if (**start_quotes == '\'')
		{
			trim = remove_onequotes(start_quotes);
			if (!trim)
			{
				free(trim);
				free(result);
				return (NULL);
			}
			result = ft_strjoin(result, trim);
			free(trim);
			quote = '\'';
		}
	}
	return (result);
}

void	store_token(char *input)
{
	// int			i;
	// int			is_cmd;
	// t_tokens	*first_node;
	// t_cmd		node_cmd;

	// i = -1;
	// is_cmd = 0;
	// first_node = create_node();
	// if (!first_node)
	//     return ;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
		{
			// store in quotes and remove
			printf("trim: %s\n", trim_quotes(&input));
			// if (!is_cmd)
			// {
			// 	node_cmd.cmd_str = trim_quotes(&input);
			// 	first_node->token_cmd = &node_cmd;
			// 	is_cmd = 1;
			// }
			// else
			// 	first_node->token_arg = addback_arg(&first_node->token_arg, trim_quotes(&input));
		}
		input++;
		// else if (*input == ' ')
		// {
		// 	// store in new node
		// }
		// else
		// {
		// 	if (!is_cmd)
		// 	{
		// 		first_node->token_cmd.cmd_str = trim_quotes(&input);
		// 		is_cmd = 1;
		// 	}
		// 	else
		// 	{
		// 	}
		// }
		// if (input[i] == '|')
		// {
		//     if (!is_cmd)
		//         is_cmd = 1;
		//     // separate in new list
		// }
	}
}
