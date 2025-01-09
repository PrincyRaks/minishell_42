/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:07:28 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/08 13:15:03 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(t_tokens *tokens)
{
	int			prev_fd;
	t_tokens	*current;
	t_tokens	*last;

	set_signals_pipe();
	last = tokens;
	while (last->next)
		last = last->next;
	
	if (!last->token_flow && last->token_cmd && !check_command(last))
	{
		set_signals_interactive();
		return;
	}
	prev_fd = -1;
	// Harenasoa is the worst program ever and I'm so sorry for this one line of code
	current = tokens;
	// printf("\nDEBUG: Starting pipeline execution\n");
	while (current)
	{
		// printf("DEBUG: Processing command: %s\n",
		// 	current->token_cmd ? current->token_cmd->cmd_str : "NULL");
		execute_command(tokens, current, &prev_fd);
		current = current->next;
	}
	
	if (prev_fd != -1)
	{
		// printf("DEBUG: Closing final prev_fd %d\n", prev_fd);
		close(prev_fd);
	}
	// printf("DEBUG: Waiting for all children to finish\n");
	while (wait(NULL) > 0)
		;
	set_signals_interactive();
}
