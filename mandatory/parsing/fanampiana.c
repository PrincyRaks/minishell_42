/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fanampiana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:15:35 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/21 15:12:54 by rrakotos         ###   ########.fr       */
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
