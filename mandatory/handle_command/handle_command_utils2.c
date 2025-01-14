/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:16:39 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/14 19:01:30 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdio(int saved_stdin, int saved_stdout)
{
	// ft_putnbr_fd(saved_stdin, 2);
	// ft_putchar_fd('\n', 2);
	// ft_putnbr_fd(saved_stdout, 2);
	// ft_putchar_fd('\n', 2);
	// dup2(saved_stdin, STDIN_FILENO);
	// dup2(saved_stdout, STDOUT_FILENO);
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
