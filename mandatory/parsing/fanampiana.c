/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fanampiana.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:15:35 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/20 17:34:38 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_tabargv(t_tokens *token)
{
	char	**argv;
	int		len_arg;
	int		i;

	len_arg = count_arg(token->token_arg);
	argv = malloc(sizeof(char *) * (len_arg + 2));
	if (!argv)
		return (NULL);
	i = 0;
	argv[i] = token->token_cmd->cmd_str;
	i++;
	while (token != NULL && i < len_arg)
	{
		argv[i] = token->token_arg->arg_cmd;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
