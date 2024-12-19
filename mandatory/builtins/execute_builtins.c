/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:41:55 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/19 09:42:12 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	execute_builtin(t_tokens *tokens, int nb)
{
	if (nb == 1)
		ft_cd(tokens);
	else if (nb == 2)
		ft_pwd();
	else if (nb == 3)
		ft_exit(tokens);
	else if (nb == 4)
		ft_echo(tokens);
	else if (nb == 5)
		ft_env();
	else if (nb == 6)
		ft_export(tokens);
	else if (nb == 7)
		ft_unset(tokens);
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