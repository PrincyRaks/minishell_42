/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:53 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/09 18:15:41 by rrakotos         ###   ########.fr       */
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
		if (data_cmd && *data_cmd != NULL && get_sigint() > 0
			&& get_sigpipe() > 0 && (*data_cmd)->errnum == DEFAULT)
			handle_command(*data_cmd);
		clean_tokens(data_cmd);
	}
}

void	reboot_data(void)
{
	t_data_env	*data;

	delete_file_tmp(get_last_file());
	set_num_file(-1);
	set_sigint(1);
	if (get_stdin_dup() > 0)
	{
		dup2(get_stdin_dup(), STDIN_FILENO);
		close(get_stdin_dup());
		set_stdin_dup(-1);
	}
	if (!get_sigpipe())
	{
		clear_export_env();
		data = get_data_env();
		clean_env(&data);
		exit(2);
	}
}

void	shell_loop(void)
{
	char		*input;

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
		if (input)
			free(input);
		reboot_data();
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
