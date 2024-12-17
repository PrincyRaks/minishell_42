/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:16:39 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/17 10:32:38 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void	handle_dots_command(t_tokens *data_cmd)
{
	if (!ft_strcmp(data_cmd->token_cmd->cmd_str, "."))
	{
		printf(" .: filename argument required\n");
		printf(".: usage: . filename [arguments]\n");
	}
	else
		printf(" %s: command not found\n", data_cmd->token_cmd->cmd_str);
}

static void	execute_external_command(char *executable, t_tokens *data_cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		set_signals_noninteractive();
		if (execve(executable, array_tokens(data_cmd), get_tabenv()) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
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
	else
		perror("fork");
}

void	handle_command(t_tokens *data_cmd)
{
	char	*executable;
	int		nb_builtin;

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
	nb_builtin = is_builtin(data_cmd->token_cmd->cmd_str);
	if (nb_builtin > 0)
		execute_builtin(data_cmd, nb_builtin);
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
