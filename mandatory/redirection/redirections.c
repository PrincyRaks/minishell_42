/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:33:48 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/23 20:45:06 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection_file(t_flow *redir)
{
	int	fd;

	if (redir->operand == OUTPUT)
		fd = open(redir->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->operand == INPUT)
		fd = open(redir->word, O_RDONLY);
	else if (redir->operand == APPEND)
		fd = open(redir->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd == -1)
		perror(redir->word);
	return (fd);
}

int	apply_redirection(t_tokens *token)
{
	t_flow	*redir;
	int		fd;

	if (!token || !token->token_flow)
		return (0);
	redir = token->token_flow;
	while (redir)
	{
		fd = open_redirection_file(redir);
		if (fd == -1)
			return (-1);
		if ((redir->operand == OUTPUT || redir->operand == APPEND)
			&& dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), close(fd), -1);
		else if (redir->operand == INPUT && dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2"), close(fd), -1);
		close(fd);
		redir = redir->next_flow;
	}
	return (0);
}

