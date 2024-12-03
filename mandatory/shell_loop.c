/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/03 11:59:45 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_tokens *tokens)
{
	char	*cmd;

	cmd = tokens->token_cmd->cmd_str;
	if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(tokens);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(tokens);
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
	pid_t pid;
	
	if(!data_cmd || !data_cmd->token_cmd)
		return; 
	// if (handle_redirections(data_cmd->token_arg) == -1)
	// 		return ; 
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
				if (execve(executable, array_tokens(data_cmd), get_tabenv()) ==
					-1)
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
			printf("command not found: %s\n", data_cmd->token_cmd->cmd_str);
	}
}

void shell_loop(void)
{
    char *input;
    t_tokens **data_cmd;

    while (1) 
    {
        input = readline("👾⇒ ");
        if (!input)
        {
            printf("exit\n");
            break ;
        }
        if (*input)
        {
            add_history(input);
            data_cmd = store_token(input);
            if (data_cmd)
			{
				handle_command(*data_cmd);
				clean_tokens(data_cmd);	
			}
        }
        free(input);
    }
}
