/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:16:39 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/16 21:44:05 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	handle_dots_command(t_tokens *data_cmd)
{
	if (!ft_strcmp(data_cmd->token_cmd->cmd_str, "."))
	{
		printf("minishell: .: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
	}
	else
		printf("minishell: %s: command not found\n", data_cmd->token_cmd->cmd_str);
}

static void	execute_external_command(char *executable, t_tokens *data_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(executable, array_tokens(data_cmd), get_tabenv()) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
		wait(NULL);
}

void	handle_command(t_tokens *data_cmd)
{
	char	*executable;

	if (!data_cmd || !data_cmd->token_cmd || !data_cmd->token_cmd->cmd_str)
		return;
	if (ft_strlen(data_cmd->token_cmd->cmd_str) <= 0)
	{
		printf(" %s: command not found.\n", data_cmd->token_cmd->cmd_str);
		return;
	}
    if (is_only_dots(data_cmd->token_cmd->cmd_str))
	{
		handle_dots_command(data_cmd);
		return;
	}
	if (is_builtin(data_cmd->token_cmd->cmd_str))
		execute_builtin(data_cmd);
	else if (data_cmd->next)
		execute_pipeline(data_cmd);
	else
	{
		executable = find_executable(data_cmd->token_cmd->cmd_str);
		if (executable)
		{
			execute_external_command(executable, data_cmd);
			free(executable);
		}
		else
			printf("%s: command not found\n", data_cmd->token_cmd->cmd_str);
	}
}
