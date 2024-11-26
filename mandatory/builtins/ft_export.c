/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:42:23 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/26 16:21:13 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void display_env(void)
{
    char    **env;

    env = get_data_export();
    while (*env != NULL)
    {        
        printf("%s\n", *env);
        env++;
    }
}

int ft_export(t_tokens *tokens)
{
	int	len_arg;

	len_arg = count_arg(tokens->token_arg);
    if(len_arg < 1)
    {
        display_env();
        return (0);
    }
    
    return (0);
}

static void    range_dataexport(char  **env)
{
    int i;
    int j;
    char    *tmp;

    i = 0;
    while (env[i] != NULL)
    {
        j = i + 1;
        while (env[j]  != NULL)
        {
            if (ft_strcmp(env[i], env[j]) > 0)
            {
                tmp = env[i];
                env[i] = env[j];
                env[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    add_var(char *var)
{
    char    **tabenv;
    int     len_tab;
    int     i;
    char    **new_env;
    char    *tmp;

    tabenv = get_data_export();
    len_tab = count_tab(tabenv);
    i = 0;
    new_env = malloc(sizeof(char*) * (len_tab + 2));
    if (!new_env)
        return;
    tmp = ft_strjoin(ft_strdup("declare -x "), var);
    new_env[i] = tmp;
    while (tabenv[i] != NULL)
    {
        new_env[i + 1] = tabenv[i];
        i++;
    }
    new_env[i + 1] = NULL;
    range_dataexport(new_env);
    set_data_export(new_env);
}
