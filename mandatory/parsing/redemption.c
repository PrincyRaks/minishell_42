/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redemption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:40:52 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/11 15:54:51 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_token(char *input)
{
	int			i;
	int			is_cmd;
	t_tokens	*first_node;
	t_cmd		node_cmd;

	i = -1;
	is_cmd = 0;
	first_node = create_node();
	if (!first_node)
		return ;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
		{
			// store in quotes and remove
			if (!is_cmd)
			{
				node_cmd.cmd_str = trim_quotes(&input);
				first_node->token_cmd = &node_cmd;
				is_cmd = 1;
			}
			else
				first_node->token_arg = addback_arg(&first_node->token_arg,
						trim_quotes(&input));
		}
		else if (*input == ' ')
		{
			// store in new node
			printf("store in new node\n");
		}
		else
		{
			if (!is_cmd)
			{
				// create function to join character while see space 
				// and if see " or ' call the function trim_quotes
				node_cmd.cmd_str = // here the function !
				first_node->token_cmd.cmd_str = trim_quotes(&input);
				is_cmd = 1;
			}
			else
			{
			}
		}
		// if (*input == '|')
		// {
		//     if (!is_cmd)
		//         is_cmd = 1;
		//     // separate in new list
		// }
	}
}
