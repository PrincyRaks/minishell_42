/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:35:58 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/09 16:08:11 by rrakotos         ###   ########.fr       */
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
	cmd->operand = NOTOP;
	cmd->errnum = DEFAULT;
	return (cmd);
}

void	clean_cmd(t_cmd *cmd)
{
	if (cmd != NULL)
	{
		if (cmd->cmd_str != NULL)
			free(cmd->cmd_str);
		free(cmd);
	}
}
