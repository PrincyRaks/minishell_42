/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:16:39 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/24 13:14:23 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_external_command(t_tokens *data_cmd)
{
	char	*executable;

	executable = find_executable(data_cmd->token_cmd->cmd_str);
	if (executable)
	{
		execute_external_command(executable, data_cmd);
		free(executable);
	}
	else
		printf("%s: command not found\n", data_cmd->token_cmd->cmd_str);
}

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void handle_command(t_tokens *data_cmd)
{
    // int saved_stdin = dup(STDIN_FILENO);
    // int saved_stdout = dup(STDOUT_FILENO);
    int nb_builtin;
    //char *executable_path;

    // if (apply_redirection(data_cmd) == -1)
    // {
    //     restore_stdio(saved_stdin, saved_stdout);
    //     return;
    // }
    // if (!data_cmd || !data_cmd->token_cmd || !data_cmd->token_cmd->cmd_str)
    // {
    //     restore_stdio(saved_stdin, saved_stdout);
    //     return;
    // }
    // executable_path = find_executable(data_cmd->token_cmd->cmd_str);
    // if (!executable_path) 
    // {
    //     restore_stdio(saved_stdin, saved_stdout);
    //     return;
    // }
    nb_builtin = is_builtin(data_cmd->token_cmd->cmd_str);
    if (nb_builtin > 0 && !data_cmd->next)
        execute_builtin(data_cmd, nb_builtin);
    else if (data_cmd->next)
        execute_pipeline(data_cmd);
    else
        handle_external_command(data_cmd);

    // free(executable_path);
    // restore_stdio(saved_stdin, saved_stdout);
}


