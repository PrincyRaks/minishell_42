/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:01:42 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/03 11:39:59 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_process(char *executable, t_tokens *data_cmd)
{
	set_signals_noninteractive();

	if (execve(executable, array_tokens(data_cmd), get_tabenv()) == -1)
	{
		if (executable[0] == '/' || 
		    (executable[0] == '.' && executable[1] == '/') || 
		    (executable[0] == '.' && executable[1] == '.' && executable[2] == '/'))
		{
			ft_putstr_fd(executable, 2);
			ft_putstr_fd(": Is a directory\n", 2);
		}
		// else
		// 	perror("execve");
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
	char	*cmd_path;

	if (!data_cmd || !data_cmd->token_cmd || !data_cmd->token_cmd->cmd_str)
		return (1);
	if (ft_strlen(data_cmd->token_cmd->cmd_str) <= 0)
		return (1);
	if (is_builtin(data_cmd->token_cmd->cmd_str))
		return (0);
	cmd_path = find_executable(data_cmd->token_cmd->cmd_str);
	if (!cmd_path)
		return (1);
	free(cmd_path);
	return (0);
}
