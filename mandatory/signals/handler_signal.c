/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 23:38:26 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/11 23:40:28 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop_instruction(int signal)
{
	int	fd[2];
	int	stdin;

	stdin = dup(STDIN_FILENO);
	set_stdin_dup(stdin);
	if (signal == SIGINT)
	{
		if (pipe(fd) < 0)
			perror("pipe");
		ft_putchar_fd('\n', fd[1]);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		set_sigint(0);
		set_status(130);
	}
}
