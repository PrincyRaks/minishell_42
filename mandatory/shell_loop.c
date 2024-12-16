/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/16 12:06:34 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_tokens *tokens)
{
	char	*cmd;

	cmd = tokens->token_cmd->cmd_str;
		ft_cd(tokens);
	if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(tokens);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env();
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(tokens);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(tokens);
	else
		ft_unset(tokens);
}
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

void	handle_command(t_tokens *data_cmd)
{
	char	*executable;
	pid_t	pid;

	if (!data_cmd || !data_cmd->token_cmd || !data_cmd->token_cmd->cmd_str)
		return;
	if (ft_strlen(data_cmd->token_cmd->cmd_str) <= 0)
	{
		printf("Command '' not found.\n");
		return;
	}
	if (is_only_dots(data_cmd->token_cmd->cmd_str))
	{
		printf("%s: command not found\n", data_cmd->token_cmd->cmd_str);
		return;
	}
	if (is_builtin(data_cmd->token_cmd->cmd_str))
		execute_builtin(data_cmd);
	else if (data_cmd->next)
		execute_pipeline(data_cmd);
	else
	{
		executable = find_executable(data_cmd->token_cmd->cmd_str);
		if (executable)
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(executable, array_tokens(data_cmd), get_tabenv()) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else if (pid > 0)
				wait(NULL);
			free(executable);
		}
		else
			printf("%s: command not found\n", data_cmd->token_cmd->cmd_str);
	}
}

void shell_loop(void)
{
    char *input;
    t_tokens **data_cmd;

    while (1) 
    {
        setup_signals();
        input = readline("👾⇒ ");
        if (!input)
        {
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }
        if (*input)
        {
            add_history(input);
            data_cmd = store_instruction(input);
            if (data_cmd)
            {
                handle_command(*data_cmd);
                clean_tokens(data_cmd);	
            }
        }
        free(input);
    }
}

