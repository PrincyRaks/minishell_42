/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:24:55 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/25 08:43:08 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	open_redirection_file(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_INPUT)
		fd = open(redir->file_name, O_RDONLY);
	else if (redir->type == REDIR_OUTPUT)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd == -1)
		perror(redir->file_name);
	return (fd);
}

int	apply_redirection(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
		}
		else
		{
			fd = open_redirection_file(redir);
			if (fd == -1)
				return (-1);
			if (redir->type == REDIR_INPUT)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}

t_redir	*create_redir(char *file_name, t_redir_type type)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->file_name = ft_strdup(file_name);
	new_redir->type = type;
	new_redir->next = NULL;
	return (new_redir);
}

void	add_redir(t_redir **head, t_redir *new_redir)
{
	t_redir	*temp;

	if (!*head)
		*head = new_redir;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*temp;

	while (redirs)
	{
		temp = redirs;
		redirs = redirs->next;
		free(temp->file_name);
		free(temp);
	}
}
