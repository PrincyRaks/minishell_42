/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:57:15 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/16 10:07:11 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signals_interactive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_print_newline(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
}

void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
