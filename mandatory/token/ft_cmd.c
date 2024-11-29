/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:35:58 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/29 08:51:50 by mrazanad         ###   ########.fr       */
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
	cmd->errnum = DEFAULT;
	return (cmd);
}

void	clean_cmd(t_cmd *cmd)
{
	if (cmd != NULL)
	{
		free(cmd->cmd_str);
		free(cmd);
	}
}
