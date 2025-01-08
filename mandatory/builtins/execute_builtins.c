/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:41:55 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/08 13:22:06 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_tokens *tokens, int nb)
{
	int exit_status;

	exit_status = 0;
	if (nb == 1)
		exit_status = ft_cd(tokens);
	else if (nb == 2)
		exit_status = ft_pwd();
	else if (nb == 3)
		exit_status = ft_exit(tokens);
	else if (nb == 4)
		exit_status = ft_echo(tokens);
	else if (nb == 5)
		exit_status = ft_env();
	else if (nb == 6)
		exit_status = ft_export(tokens);
	else if (nb == 7)
		exit_status = ft_unset(tokens);
	(void)exit_status;	
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (2);
	else if (!ft_strcmp(cmd, "exit"))
		return (3);
	else if (!ft_strcmp(cmd, "echo"))
		return (4);
	else if (!ft_strcmp(cmd, "env"))
		return (5);
	else if (!ft_strcmp(cmd, "export"))
		return (6);
	else if (!ft_strcmp(cmd, "unset"))
		return (7);
	return (0);
}
