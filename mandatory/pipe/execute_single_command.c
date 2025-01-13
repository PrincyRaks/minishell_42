/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:08:18 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/13 20:42:30 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_empty_command(char *executable, char **argv)
{
	ft_putendl_fd("Command '' not found.", 2);
	free(executable);
	free_array(argv);
	exit(127);
}

static void	execute_the_command(char *executable, char **argv, char **tab_env)
{
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

void	execute_single_command(t_tokens *tokens)
{
	char	*executable;
	char	**argv;
	char	*cmd;
	char	**tab_env;

	cmd = tokens->token_cmd->cmd_str;
	if (is_builtin(cmd))
	{
		execute_builtin(tokens, is_builtin(cmd));
		clean_up_exit(get_status());
	}
	executable = find_executable(cmd);
	argv = array_tokens(tokens);
	if (tokens->token_flow && apply_redirection(tokens) == -1)
	{
		free(executable);
		free_array(argv);
		exit(1);
	}
	if (cmd && cmd[0] == '\0')
		handle_empty_command(executable, argv);
	tab_env = get_tabenv();
	execute_the_command(executable, argv, tab_env);
}
