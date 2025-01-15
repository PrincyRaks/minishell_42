/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:16:39 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/15 16:38:46 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	if (saved_stdin != -1)
	{
		close(saved_stdin);
		set_stdin_dup(-1);
	}
	if (saved_stdout != -1)
	{
		close(saved_stdout);
		set_stdout_dup(-1);
	}
}
