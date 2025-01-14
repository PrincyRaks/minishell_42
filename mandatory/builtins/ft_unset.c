/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:48:19 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/14 15:48:14 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_data_env **env, char *key)
{
	t_data_env	*tmp;
	t_data_env	*prev;

	tmp = *env;
	prev = NULL;
	if (tmp != NULL && !ft_strcmp(tmp->key, key))
	{
		*env = (*env)->next;
		set_data_env(*env);
		clean_node_env(tmp);
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->key, key) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	clean_node_env(tmp);
	load_data_export();
}

int	ft_unset(t_tokens *tokens)
{
	t_arg		*argv;
	t_data_env	*env;

	env = get_data_env();
	argv = tokens->token_arg;
	while (argv != NULL)
	{
		delete_node(&env, argv->arg_str);
		argv = argv->next_arg;
	}
	return (0);
}
