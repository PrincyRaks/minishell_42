/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:25:56 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/16 12:15:47 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_one_dot(char *cmd, int saved_stdin, int saved_stdout)
{
	(void)cmd;
	(void)saved_stdin;
	(void)saved_stdout;
	ft_putstr_fd(" : .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	clean_up_exit(2);
}

static void	execute_command_type(t_tokens *data_cmd, t_cmd *cmd,
		int saved_stdin, int saved_stdout)
{
	int	nb_builtin;

	nb_builtin = is_builtin(cmd->cmd_str);
	if (nb_builtin > 0 && !data_cmd->next)
	{
		if (apply_redirection(data_cmd) == -1)
		{
			set_status(1);
			restore_stdio(saved_stdin, saved_stdout);
			return ;
		}
		execute_builtin(data_cmd, nb_builtin);
		restore_stdio(saved_stdin, saved_stdout);
		return ;
	}
	if (data_cmd)
	{
		execute_pipeline(data_cmd);
		restore_stdio(saved_stdin, saved_stdout);
		return ;
	}
	restore_stdio(saved_stdin, saved_stdout);
}

void	handle_command(t_tokens *data_cmd)
{
	int		saved_stdin;
	int		saved_stdout;
	t_cmd	*node_cmd;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	set_stdin_dup(saved_stdin);
	set_stdout_dup(saved_stdout);
	if (!data_cmd)
	{
		restore_stdio(saved_stdin, saved_stdout);
		return ;
	}
	node_cmd = data_cmd->token_cmd;
	execute_command_type(data_cmd, node_cmd, saved_stdin, saved_stdout);
}
