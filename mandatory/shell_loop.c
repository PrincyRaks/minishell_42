/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/17 15:38:34 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_tokens *tokens, int nb)
{
	if (nb == 1)
		ft_cd(tokens);
	else if (nb == 2)
		ft_pwd();
	else if (nb == 3)
		ft_exit(tokens);
	else if (nb == 4)
		ft_echo(tokens);
	else if (nb == 5)
		ft_env();
	else if (nb == 6)
		ft_export(tokens);
	else if (nb == 7)
		ft_unset(tokens);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (2);
	else if (!ft_strcmp(cmd, "exit"))
		return (3);
	else if (!ft_strcmp(cmd, "echo"))
		return (4);
	else if (!ft_strcmp(cmd, "env"))
		return (5);
	else if (!ft_strcmp(cmd, "export"))
		return (6);
	else if (!ft_strcmp(cmd, "unset"))
		return (7);
	return (0);
}

void	shell_loop(void)
{
	char		*input;
	t_tokens	**data_cmd;

	while (1)
	{
		set_signals_interactive();
		input = readline(PROMPT);
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (*input == '|')
			{
				printf(": syntax error near unexpected token `|'\n");
				continue ;
			}
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
