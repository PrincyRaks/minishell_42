/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:42:23 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/27 17:31:34 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_env(void)
{
	char	**env;

	env = get_data_export();
	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
// 1 sans valeur / negative is error / 2
static int check_type_argv(char *arg_str)
{
	if (ft_isalpha())
	while (*arg_str)
	{
	}
}

static void handle_arg(t_arg *argv, int len_arg)
{
    if (!argv)
        return ;
    while (argv != NULL)
    {
    }
}

int	ft_export(t_tokens *tokens)
{
	int	len_arg;

	len_arg = count_arg(tokens->token_arg);
	if (len_arg < 1)
	{
		display_env();
		return (0);
	}
	return (0);
}

static int	cmp_key(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '=' || s1[i] != '\0') && (s2[i] != '='
			|| s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

static void	range_data_export(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i] != NULL)
	{
		j = i + 1;
		while (env[j] != NULL)
		{
			if (cmp_key(env[i], env[j]) > 0)
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
// rah key fotsiny
void	add_var(char *var)
{
	char	**tabenv;
	int		len_tab;
	int		i;
	char	**new_env;
	char	*tmp;

	tabenv = get_data_export();
	len_tab = count_tab(tabenv);
	i = 0;
	new_env = malloc(sizeof(char *) * (len_tab + 2));
	if (!new_env)
		return ;
	tmp = ft_strjoin(ft_strdup("declare -x "), var);
	new_env[i] = tmp;
	while (tabenv[i] != NULL)
	{
		new_env[i + 1] = tabenv[i];
		i++;
	}
	new_env[i + 1] = NULL;
	range_data_export(new_env);
	set_data_export(new_env);
	free(tabenv);
}
