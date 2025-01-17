/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:08:18 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/17 08:41:47 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_empty_command(char *executable, char **argv)
{
	ft_putendl_fd("Command '' not found.", 2);
	free(executable);
	free_array(argv);
	clean_up_exit(127);
}

static void	execute_the_command(char *executable, char **argv, char **tab_env)
{
	if (!executable || !argv || execve(executable, argv, tab_env) == -1)
	{
		if (!executable)
			set_status(0);
		else
			set_status(127);
		free(executable);
		free_array(argv);
		free_array(tab_env);
		clean_up_exit(get_status());
	}
	free(executable);
	free_array(tab_env);
	free_array(argv);
}

void	execute_single_command(t_tokens *tokens)
{
	char	*executable;
	char	**argv;
	char	*cmd;

	cmd = tokens->token_cmd->cmd_str;
	executable = find_executable(cmd);
	argv = array_tokens(tokens);
	if (tokens->token_flow && apply_redirection(tokens) == -1)
	{
		free(executable);
		free_array(argv);
		set_status(1);
		clean_up_exit(1);
	}
	if (is_builtin(cmd))
	{
		free(executable);
		free_array(argv);
		execute_builtin(tokens, is_builtin(cmd));
		clean_up_exit(get_status());
	}
	if (cmd && cmd[0] == '\0')
		handle_empty_command(executable, argv);
	execute_the_command(executable, argv, get_tabenv());
}
