/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:01:42 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/19 10:02:25 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_dots_command(t_tokens *data_cmd)
{
	if (!ft_strcmp(data_cmd->token_cmd->cmd_str, "."))
	{
		printf(" .: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
	}
	else
		printf(" %s: command not found\n", data_cmd->token_cmd->cmd_str);
}

void	handle_child_process(char *executable, t_tokens *data_cmd)
{
	set_signals_noninteractive();
	if (execve(executable, array_tokens(data_cmd), get_tabenv()) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	handle_parent_process(pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	set_signals_interactive();
	if (status & 0x7F)
	{
		if ((status & 0x7F) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if ((status & 0x7F) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
}

void	execute_external_command(char *executable, t_tokens *data_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		handle_child_process(executable, data_cmd);
	else if (pid > 0)
		handle_parent_process(pid);
	else
		perror("fork");
}

int	is_invalid_command(t_tokens *data_cmd)
{
	if (!data_cmd || !data_cmd->token_cmd || !data_cmd->token_cmd->cmd_str)
		return (1);
	if (ft_strlen(data_cmd->token_cmd->cmd_str) <= 0)
	{
		printf(" %s: command not found.\n", data_cmd->token_cmd->cmd_str);
		return (1);
	}
	return (0);
}
