/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:08:18 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/26 10:25:04 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_command(t_tokens *token)
{
	char	*executable;
	char	**args;

	if (!token || !token->token_cmd || !token->token_cmd->cmd_str)
		exit(EXIT_FAILURE);
	executable = find_executable(token->token_cmd->cmd_str);
	if (!executable)
	{
		printf("command not found: %s\n", token->token_cmd->cmd_str);
		exit(127);
	}
	args = array_tokens(token);
	if (execve(executable, args, get_tabenv()) == -1)
	{
		perror("execve");
		free(args);
		free(executable);
		exit(EXIT_FAILURE);
	}
	free(args);
	free(executable);
}
