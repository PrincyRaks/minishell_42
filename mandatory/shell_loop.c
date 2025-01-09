/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/09 16:37:49 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_input(char *input)
{
	t_tokens	**data_cmd;

	if (*input)
	{
		add_history(input);
		// if (*input == '|')
		// {
		// 	printf(": syntax error near unexpected token `|'\n");
		// 	return ;
		// }
		data_cmd = store_instruction(input);
		if (data_cmd && *data_cmd != NULL && get_sigint_hd() > 0
			&& get_sigpipe() > 0 && (*data_cmd)->errnum == DEFAULT)
			handle_command(*data_cmd);
		clean_tokens(data_cmd);
	}
}

void	shell_loop(void)
{
	char		*input;
	t_data_env	*data;

	set_signals_interactive();
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		handle_input(input);
		free(input);
		delete_file_tmp(get_last_file());
		set_num_file(-1);
		set_sigint_hd(1);
		if (!get_sigpipe())
		{
			clear_export_env();
			data = get_data_env();
			clean_env(&data);
			exit(2);
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
