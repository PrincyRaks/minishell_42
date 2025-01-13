/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:08:18 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/13 18:04:27 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_command(t_tokens *tokens)
{
	char	*executable;
	char	**argv;
	char	*cmd;
	char 	**tab_env;

	cmd = tokens->token_cmd->cmd_str;
	if (is_builtin(cmd))
	{
		execute_builtin(tokens, is_builtin(cmd));
		clean_up_exit(get_status());
		// exit(0);
		// if (count_token(tokens) > 1)
	}
	executable = find_executable(cmd);
	argv = array_tokens(tokens);
	if (tokens->token_flow)
	{
		if (apply_redirection(tokens) == -1)
		{
			free(executable);
			free_array(argv);
			exit(1);
		}
	}
	if (cmd && cmd[0] == '\0')
	{
		ft_putendl_fd("Command '' not found.", 2);
		free(executable);
		free_array(argv);
		exit(127);
	}
	tab_env = get_tabenv();
	if (!executable || !argv || execve(executable, argv, tab_env) == -1)
	{
		free(executable);
		free_array(argv);
		free_array(tab_env);
		clean_up_exit(errno);
	}
	free(executable);
	free_array(tab_env);
	free_array(argv);
}
