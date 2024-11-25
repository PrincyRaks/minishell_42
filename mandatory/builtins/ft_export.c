/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:42:23 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/25 16:01:37 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_env(void)
{
    int         len_data;
	t_data_env	*data_env;
	char		**array_data;
    int         i;
    t_data_env  *var_env;

	data_env = get_data_env();
    len_data = count_data_env(data_env);
	array_data = malloc(sizeof(char *) * (len_data + 1));
    i = 0;
    while (i < len_data)
    {
        if (ft_strcmp(data_env->key, data_env->next->key) < 0)
        {
            var_env = data_env;
            data_env = data_env->next;
        }
    }
    
}

int	ft_export(t_tokens *tokens)
{
	int	len_arg;

	len_arg = count_arg(tokens->token_arg);
}
