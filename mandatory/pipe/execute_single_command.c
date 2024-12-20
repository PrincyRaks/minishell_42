/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:08:18 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/20 10:41:01 by mrazanad         ###   ########.fr       */
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
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("%s: command not found\n", tokens->token_cmd->cmd_str);
		exit(127);
	}
	argv = array_tokens(tokens);
	if (execve(executable, argv, get_tabenv()) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
