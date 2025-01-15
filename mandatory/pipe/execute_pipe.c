/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:07:28 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/15 11:10:10 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(t_tokens *tokens)
{
	int			prev_fd;
	t_tokens	*current;

	set_signals_pipe();
	prev_fd = -1;
	current = tokens;
	while (current)
	{
		execute_command(tokens, current, &prev_fd);
		current = current->next;
	}
	if (prev_fd != -1)
	{
		ft_putstr_fd("ATO VEE\n", 2);
		close(prev_fd);
	}
	while (wait(NULL) > 0)
		;
	set_signals_interactive();
}
