/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:08:18 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/09 18:34:20 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_command(t_tokens *tokens)
{
	char	*executable;
	char	**argv;
	char	*cmd;

	cmd = tokens->token_cmd->cmd_str;
	if (is_builtin(cmd))
	{
		execute_builtin(tokens, is_builtin(cmd));
		exit(0); // esorina refa anao exit status
	}
	executable = find_executable(cmd);
	if (!executable && !is_builtin(cmd))
	{
		if (cmd[0] != '/' && cmd[0] != '.')
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(" : command not found\n", 2);
		}
		exit(127);
	}
	argv = array_tokens(tokens);
	if (tokens->token_flow)
		apply_redirection(tokens);
	if (cmd && cmd[0] == '\0')
	{
		ft_putendl_fd("Command '' not found.", 2);
		free(executable);
		free_array(argv);
		exit(127);
	}
	if (!ft_strcmp(cmd, "."))
	{
		handle_dot_command(cmd, -1, -1);
		free(executable);
		free_array(argv);
		exit(2);
	}
	if (execve(executable, argv, get_tabenv()) == -1)
	{
		// perror(cmd);
		free(executable);
		free_array(argv);
		exit(126);
	}
	free(executable);
	free_array(argv);
}
