/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:58:22 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/26 13:55:59 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	perror("pwd");
	return (1);
}
