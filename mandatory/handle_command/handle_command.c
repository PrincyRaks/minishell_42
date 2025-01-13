/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:25:56 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/13 20:32:25 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_one_dot(char *cmd, int saved_stdin, int saved_stdout)
{
	(void)cmd;
	ft_putstr_fd(" : .: filename argument required\n", 2);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	restore_stdio(saved_stdin, saved_stdout);
}

static void	execute_command_type(t_tokens *data_cmd, t_cmd	*cmd, int saved_stdin,
		int saved_stdout)
{
	int	nb_builtin;

	nb_builtin = is_builtin(cmd->cmd_str);
	if (nb_builtin > 0 && !data_cmd->next)
	{
		execute_builtin(data_cmd, nb_builtin);
		return (restore_stdio(saved_stdin, saved_stdout));
	}
	if (data_cmd)
	{
		execute_pipeline(data_cmd);
		return (restore_stdio(saved_stdin, saved_stdout));
	}
	return ;
	restore_stdio(saved_stdin, saved_stdout);
}

void	handle_command(t_tokens *data_cmd)
{
	int		saved_stdin;
	int		saved_stdout;
	t_cmd	*node_cmd;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!data_cmd)
		return (restore_stdio(saved_stdin, saved_stdout));
	node_cmd = data_cmd->token_cmd;
	execute_command_type(data_cmd, node_cmd, saved_stdin, saved_stdout);
	restore_stdio(saved_stdin, saved_stdout);
}

