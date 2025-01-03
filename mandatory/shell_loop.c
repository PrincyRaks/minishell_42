/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/03 17:30:24 by mrazanad         ###   ########.fr       */
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
		if (data_cmd && *data_cmd != NULL)
		{
//       if ((*data_cmd)->token_flow != NULL)
// 				execute_redirection(*data_cmd);
			handle_command(*data_cmd);
			clean_tokens(data_cmd);
		}
	}
}

/* static void	process_input(void)
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
} */

void	shell_loop(void)
{
	char	*input;
	
	set_signals_interactive();
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break;
		}
		handle_input(input);
		free(input);	
	}
}
