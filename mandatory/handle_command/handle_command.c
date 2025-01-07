/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 18:25:56 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/07 16:29:06 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_dot_command(char *cmd, int saved_stdin, int saved_stdout)
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
	if (data_cmd->next)
	{
		execute_pipeline(data_cmd);
		return (restore_stdio(saved_stdin, saved_stdout));
	}
	// if (!find_executable(cmd))
	// 	return (handle_executable_error(cmd, saved_stdin, saved_stdout));
	check_command(data_cmd);
	handle_external_command(data_cmd);
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
	if (apply_redirection(data_cmd) == -1)
		return (restore_stdio(saved_stdin, saved_stdout));
	node_cmd = data_cmd->token_cmd;
	if ((!node_cmd->cmd_str || !ft_strlen(node_cmd->cmd_str)) && !data_cmd->token_flow)
	{
		ft_putstr_fd("Command '' not found.\n", 2);
		restore_stdio(saved_stdin, saved_stdout);
		return ;
	}
	if (node_cmd != NULL && node_cmd->cmd_str != NULL)
	{
		if (!ft_strcmp(node_cmd->cmd_str, "."))
			return (handle_dot_command(node_cmd->cmd_str, saved_stdin, saved_stdout));
		execute_command_type(data_cmd, node_cmd, saved_stdin, saved_stdout);
	}
	restore_stdio(saved_stdin, saved_stdout);
}

// void	handle_path_command(char *cmd, int saved_stdin, int saved_stdout)
// {
// 	// if (is_only_dots(cmd))
// 	// {
// 	// 	ft_putstr_fd(" : ", 2);
// 	// 	ft_putstr_fd(cmd, 2);
// 	// 	ft_putstr_fd(": ty command not found\n", 2);
// 	// }
// 	if (access(cmd, F_OK) != 0)
// 	{
// 		ft_putstr_fd(" : ", 2);
// 		ft_putstr_fd(cmd, 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 	}
// 	else if (access(cmd, X_OK) != 0)
// 	{
// 		ft_putstr_fd(" : ", 2);
// 		ft_putstr_fd(cmd, 2);
// 		ft_putstr_fd(": Permission denied\n", 2);
// 	}
// 	/* else if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '.'
// 			&& cmd[1] == '.' && cmd[2] == '/'))
// 	{
// 		ft_putstr_fd(cmd, 2);
// 		ft_putstr_fd(": Is a directory\n", 2);
// 	} */
// 	restore_stdio(saved_stdin, saved_stdout);
// }

// static void	handle_executable_error(char *cmd, int saved_stdin,
// 		int saved_stdout)
// {
// 	ft_putstr_fd(" : ", 2);
// 	ft_putstr_fd(cmd, 2);
// 	ft_putstr_fd(": command not found\n", 2);
// 	restore_stdio(saved_stdin, saved_stdout);
// }