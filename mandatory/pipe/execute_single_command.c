/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:08:18 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/03 13:45:21 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	execute_single_command(t_tokens *tokens)
{
	char	*executable;
	char	**argv;
	char	*cmd;

	cmd = tokens->token_cmd->cmd_str;
	executable = find_executable(cmd);
	if (!executable)
	{
		if (cmd[0] != '/' && cmd[0] != '.')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		exit(127);
	}
	argv = array_tokens(tokens);
	if (execve(executable, argv, get_tabenv()) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmd);
		free(executable);
		free_array(argv);
		exit(126);
	}
	free(executable);
	free_array(argv);
}
