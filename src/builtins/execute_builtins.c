/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:41:55 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/09 16:43:20 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_tokens *tokens, int nb)
{
	if (nb == 1)
		set_status(ft_cd(tokens));
	else if (nb == 2)
		set_status(ft_pwd());
	else if (nb == 3)
		set_status(ft_exit(tokens));
	else if (nb == 4)
		set_status(ft_echo(tokens));
	else if (nb == 5)
		set_status(ft_env(tokens));
	else if (nb == 6)
		set_status(ft_export(tokens));
	else if (nb == 7)
		set_status(ft_unset(tokens));
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
