/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:46:43 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/21 15:27:54 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_tokens *tokens)
{
	t_data_env	*home;
	int			len_arg;
	char		*error;

	len_arg = 0;
	// if (!tokens)
	// 	return (1);
	len_arg = count_arg(tokens->token_arg);
	if (len_arg > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else if (len_arg < 1)
	{
		home = ft_getenv("HOME");
		if (!home)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
		if (chdir(home->value) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else
	{
		if (chdir(tokens->token_arg->arg_str) != 0)
		{
			error = ft_strjoin(ft_strdup("cd: "), tokens->token_arg->arg_str);
			perror(error);
			free(error);
			return (1);
		}
	}
	return (0);
}
