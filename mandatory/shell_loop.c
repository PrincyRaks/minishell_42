/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/26 10:22:51 by mrazanad         ###   ########.fr       */
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
            break;
        }
        if (*input)
        {
            add_history(input);
            data_cmd = store_token(input);
            if (data_cmd != NULL && *data_cmd != NULL)
            {
                execute_pipeline(*data_cmd);
                // Libérer la mémoire si nécessaire pour éviter les fuites
                free_tokens(data_cmd);
            }
        }
        free(input);
    }
}



