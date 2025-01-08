/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:16:39 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/08 13:05:35 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_external_command(t_tokens *data_cmd)
{
	char	*executable;

	ft_putendl_fd("HEHEHEHEHE\n", 2);
	executable = find_executable(data_cmd->token_cmd->cmd_str);
	if (executable)
	{
		execute_external_command(executable, data_cmd);
		free(executable);
	}
}

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
