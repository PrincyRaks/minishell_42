/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:08:18 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/31 10:18:08 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_command(t_tokens *tokens)
{
	char	*executable;
	char	**argv;

	executable = find_executable(tokens->token_cmd->cmd_str);
	if (!executable)
	{
		ft_putstr_fd(tokens->token_cmd->cmd_str, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	argv = array_tokens(tokens);
	if (execve(executable, argv, get_tabenv()) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
