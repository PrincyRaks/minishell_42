/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:33:25 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/13 18:02:15 by mrazanad         ###   ########.fr       */
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
	argv[i] = ft_strdup(token->token_cmd->cmd_str);
	i++;
	tmp = token->token_arg;
	while (tmp != NULL && i < len_arg)
	{
		if (!tmp->arg_str)
			argv[i] = NULL;
		else
			argv[i] = ft_strdup(tmp->arg_str);
		tmp = tmp->next_arg;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

int	create_new_token(t_tokens **first_node, t_tokens **node_token)
{
	if (!node_token && !*node_token)
		return (0);
	*node_token = new_token();
	if (!node_token)
		return (0);
	addback_token(first_node, *node_token);
	return (1);
}
