/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:07:28 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/07 18:49:06 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_data_flow(t_flow *flow)
// {
// 	while (flow)
// 	{
// 		if (flow->word)
// 		{
// 			ft_putstr_fd(">>> ", 2);
// 			ft_putendl_fd(flow->word, 2);
// 		}
// 		flow = flow->next_flow;
// 	}
// }

void	execute_pipeline(t_tokens *tokens)
{
	int			prev_fd;
	t_tokens	*current;
	t_tokens	*last;

	set_signals_pipe();
	last = tokens;
	while (last->next)
		last = last->next;
	/* if (last && last->token_cmd && last->token_cmd->cmd_str && last->token_flow)
	{
		apply_redirection(last);
		set_signals_interactive();
		return ;
	} */
	if (!check_command(last))
	{
		set_signals_interactive();
		return ;
	}
	prev_fd = -1;
	current = last;
	while (current)
	{
		execute_command(tokens, current, &prev_fd);
		current = get_prev_token(tokens, current);
	}
	while (wait(NULL) > 0)
		;
	set_signals_interactive();
}
