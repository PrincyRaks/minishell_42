/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:07:28 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/20 10:13:20 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(t_tokens *tokens)
{
	int		pipe_fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	while (tokens)
	{
		if (tokens->next && pipe(pipe_fd) == -1)
			exit_perror("pipe");
		pid = fork();
		if (pid == -1)
			exit_perror("fork");
		if (pid == 0)
			handle_child(prev_fd, pipe_fd, tokens);
		prev_fd = handle_parent(prev_fd, pipe_fd, tokens);
		tokens = tokens->next;
	}
	wait_for_children();
}
