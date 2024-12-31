/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/31 10:55:17 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input(char *input)
{
	t_tokens	**data_cmd;

	if (*input)
	{
		add_history(input);
		if (*input == '|')
		{
			printf(": syntax error near unexpected token `|'\n");
			return ;
		}
		data_cmd = store_instruction(input);
		if (data_cmd)
		{
			handle_command(*data_cmd);
			clean_tokens(data_cmd);
		}
	}
}

static void	process_input(void)
{
	char	*input;

	set_signals_interactive();
	input = readline(PROMPT);
	if (!input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
	handle_input(input);
	free(input);
}

void	shell_loop(void)
{
	while (1)
		process_input();
}
