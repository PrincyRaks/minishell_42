/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/16 21:23:56 by mrazanad         ###   ########.fr       */
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
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "echo") == 0) 
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0;
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
