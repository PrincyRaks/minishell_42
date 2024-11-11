/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:46:43 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/11 14:22:58 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	const char	*home;

	if (!args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if (chdir(home) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}
