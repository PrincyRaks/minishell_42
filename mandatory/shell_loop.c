/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/26 15:18:39 by mrazanad         ###   ########.fr       */
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

int	is_pipe_without_command(t_tokens *data_cmd)
{
	t_tokens	*current;

	current = data_cmd;
	while (current != NULL)
	{
		if (ft_strcmp(current->token_cmd->cmd_str, "|") == 0)
		{
			if (current->next == NULL || (current->next != NULL
					&& current->next->token_cmd->cmd_str == NULL))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

void	handle_command(t_tokens *data_cmd)
{
	char	*executable;

	if (is_builtin(data_cmd->token_cmd->cmd_str))
		execute_builtin(data_cmd);
	else if (data_cmd->next)
		execute_pipeline(data_cmd);
	else
	{
		executable = find_executable(data_cmd->token_cmd->cmd_str);
		if (executable)
		{
			if (fork() == 0)
			{
				if (execve(executable, array_tokens(data_cmd), get_tabenv()) ==
					-1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else
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
            if (data_cmd != NULL && *data_cmd != NULL)
            {
                if (is_pipe_without_command(*data_cmd))
                {
                    printf("> ");
                    free(input);
                    continue;
                }
                handle_command(*data_cmd);
                free_tokens(data_cmd);
            }
            else
                printf("minishell: syntax error near unexpected token `|`\n");
        }
        free(input);
    }
}

