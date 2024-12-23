/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:33:48 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/23 18:28:33 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redirection_file(t_flow *redir)
{
	int	fd;

	fd = -1;
	if (redir->operand == OUTPUT)
		fd = open(redir->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->operand == INPUT)
		fd = open(redir->word, O_RDONLY);
	// else if (redir->operand == APPEND)
	//     fd = open(redir->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

    int stdin = dup(STDIN_FILENO);
    int stdout = dup(STDOUT_FILENO);
	if (!token || !token->token_flow)
		return (0);
	redir = token->token_flow;
	while (redir)
	{
		fd = open_redirection_file(redir);
		if (fd == -1)
		{
			token->errnum = ERRFLOW;
			return (-1);
		}
        if (redir->operand == OUTPUT)
		{
			printf("bola\n");
            dup2(fd, STDOUT_FILENO);
		}
		else
		    dup2(fd, STDIN_FILENO);
		close(fd);
		redir = redir->next_flow;
	}
	(void)stdin;
	(void)stdout;
    dup2(stdin, STDIN_FILENO);
    dup2(stdout, STDOUT_FILENO);
    close(stdin);
    close(stdout);
	return (0);
}
