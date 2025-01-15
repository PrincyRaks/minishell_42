/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:31:19 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/15 16:31:02 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data_env	*data;

	(void)argc;
	(void)argv;
	dup_env(envp);
	shell_loop();
	clear_export_env();
	data = get_data_env();
	clean_env(&data);
	clear_history();
	restore_stdio(get_stdin_dup(), get_stdout_dup());
	return (get_status());
}
