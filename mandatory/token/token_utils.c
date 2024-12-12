/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:33:25 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/20 12:30:32 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**array_tokens(t_tokens *token)
{
	int		i;
	char	**argv;
	int		len_arg;
	t_arg	*tmp;

	len_arg = count_arg(token->token_arg);
	if (len_arg < 1 && !token->token_cmd->cmd_str)
	{
		argv = malloc(sizeof(char *));
		*argv = NULL; 
		return (argv);
	}	
	len_arg += 2;
	argv = malloc(sizeof(char *) * len_arg);
	if (!argv)
		return (NULL);
	i = 0;
	argv[i] = token->token_cmd->cmd_str;
	i++;
	tmp = token->token_arg;
	while (tmp != NULL && i < len_arg)
	{
		argv[i] = tmp->arg_str;
		tmp = tmp->next_arg;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
