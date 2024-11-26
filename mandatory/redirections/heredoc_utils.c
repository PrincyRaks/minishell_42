/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:01:43 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/25 08:52:58 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir_from_fd(int fd, t_redir_type type)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->file_name = NULL;
	new_redir->heredoc_fd = fd;
	new_redir->type = type;
	new_redir->next = NULL;
	return (new_redir);
}

char	*read_heredoc_line(void)
{
	char	*line;

	line = readline("");
	return (line);
}

void	process_heredoc(int pipe_fd[2], char *delim)
{
	char	*line;

	while (1)
	{
		printf("heredoc>");
		line = read_heredoc_line();
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
}

int	handle_heredoc(char **args, int *i, t_redir **redirs)
{
	char	*delim;
	int		pipe_fd[2];

	delim = args[*i + 1];
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	process_heredoc(pipe_fd, delim);
	close(pipe_fd[1]);
	add_redir(redirs, create_redir_from_fd(pipe_fd[0], REDIR_HEREDOC));
	*i += 2;
	return (1);
}
