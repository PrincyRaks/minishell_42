/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:35:58 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/14 14:20:33 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_str = NULL;
	cmd->is_cmd = 0;
	return (cmd);
}

void	clean_cmd(t_cmd *cmd)
{
	free(cmd->cmd_str);
	free(cmd);
}

// init instr->token_cmd.is_cmd
int	check_cmd(t_cmd cmd)
{
	// return 0 or -1
}
