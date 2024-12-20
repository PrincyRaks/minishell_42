/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:33:33 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/20 11:21:58 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void setup_pipe(int prev_fd, int pipe_fd[2], t_tokens *tokens)
{
    if (prev_fd != -1)
    {
        printf("[DEBUG] Duping prev_fd to STDIN\n");
        if (dup2(prev_fd, STDIN_FILENO) == -1)
        {
            perror("[DEBUG] dup2 prev_fd failed");
            exit(EXIT_FAILURE);
        }
        close(prev_fd);
    }
    if (tokens->next) // Si une commande suit
    {
        printf("[DEBUG] Duping pipe_fd[1] to STDOUT\n");
        close(pipe_fd[0]);
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        {
            perror("[DEBUG] dup2 pipe_fd[1] failed");
            exit(EXIT_FAILURE);
        }
        close(pipe_fd[1]);
    }
}


void	wait_for_children(void)
{
	int	status;

	while (wait(&status) > 0)
		;
}


void	handle_child(int prev_fd, int pipe_fd[2], t_tokens *tokens)
{
	setup_pipe(prev_fd, pipe_fd, tokens);
	execute_single_command(tokens);
	exit(127);
}

int	handle_parent(int prev_fd, int pipe_fd[2], t_tokens *tokens)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (tokens->next)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	return (-1);
}

void	exit_perror(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
