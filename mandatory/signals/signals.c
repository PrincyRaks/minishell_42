/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:57:15 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/16 10:35:24 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	//rl_on_new_line();             
	rl_replace_line("", 0);       
	rl_redisplay();               
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);  
	signal(SIGQUIT, SIG_IGN);        
}

void	check_eof(char *input)
{
	if (input == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(0);
	}
}
