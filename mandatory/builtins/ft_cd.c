/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:46:43 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/22 19:29:06 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dir_home()
{
	t_data_env	*home;

	home = ft_getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	else if (chdir(home->value) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static int	safe_chdir(char *dir)
{
	int	status;
	char		*error;

	status = chdir(dir)  == 0;
	if (status)
		return (0);
	error = ft_strjoin(ft_strdup("cd: "), dir);
	perror(error);
	free(error);
	return (1);
}

// static int safe_getcwd(){}

int	ft_cd(t_tokens *tokens)
{
	int			len_arg;
	char		cwd[PATH_MAX];
	static char	*prev_dir = NULL;
		

	// if (!tokens)
	// 	return (1);
	len_arg = count_arg(tokens->token_arg);
	if (len_arg > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else if (len_arg < 1)
		return (dir_home());
	else
	{
		if (!ft_strcmp(tokens->token_arg->arg_str, "~") 
			|| !ft_strcmp(tokens->token_arg->arg_str, "--"))
			return (dir_home());
		else if (!ft_strcmp(tokens->token_arg->arg_str, "-") && prev_dir != NULL)
		{
			printf("%s\n", prev_dir);
			return (safe_chdir(prev_dir));
		}
		else
		{
			prev_dir = getcwd(cwd, sizeof(cwd));
			return (safe_chdir(tokens->token_arg->arg_str));
		}
	}
	return (0);
}
