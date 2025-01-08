/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:33:48 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/08 14:02:28 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection_file(t_flow *redir)
{
	int	fd;

	fd = -1;
	if (!redir || !redir->word || !ft_strlen(redir->word))
	{
		ft_putstr_fd(" : No such file or directory\n", 2);
		return (-1);
	}
	if (redir->operand == INPUT)
	{
		printf("hehe: %s\n", redir->word);
		fd = open(redir->word, O_RDONLY);
	}
	else if (redir->operand == OUTPUT)
		fd = open(redir->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->operand == APPEND)
		fd = open(redir->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_putstr_fd(" : No such file or directory\n", 2);
	return (fd);
}

static int	handle_output_redirection(t_flow *redir, int fd)
{
	(void)redir;
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	return (0);
}

static int	handle_input_redirection(t_flow *redir, int fd)
{
	(void)redir;
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	return (0);
}

static int	apply_single_redirection(t_flow *redir)
{
	int	fd;
	int	ret;

	fd = open_redirection_file(redir);
	if (fd == -1)
		return (-1);
	if (redir->operand == OUTPUT || redir->operand == APPEND)
		ret = handle_output_redirection(redir, fd);
	else if (redir->operand == INPUT || redir->operand == HEREDOC)
		ret = handle_input_redirection(redir, fd);
	else
		ret = 0;
	close(fd);
	return (ret);
}

int	apply_redirection(t_tokens *token)
{
	t_flow	*redir;

	if (!token || !token->token_flow)
		return (0);
	redir = token->token_flow;
	while (redir)
	{
		if (apply_single_redirection(redir) == -1)
			return (-1);
		redir = redir->next_flow;
	}
	return (0);
}
