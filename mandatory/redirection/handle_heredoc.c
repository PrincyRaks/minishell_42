/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:43:57 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/08 14:00:18 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_heredoc(int signal)
{
	int fd[2];
	int stdin;

	stdin = dup(STDIN_FILENO);
	set_stdin_dup(stdin);
	if (signal == SIGINT)
	{
		if (pipe(fd) < 0)
			perror("pipe");
		ft_putchar_fd('\n', fd[1]);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		set_sigint_hd(0);
	}
}

int	create_file_tmp(t_flow *heredoc)
{
	int			fd_tmp;
	char		*path_name;
	int			next_file;

	set_folder_tmp(&path_name);
	if (!path_name)
		return (-1);
	next_file = get_last_file();
	next_file++;
	set_num_file(next_file);
	path_name = concat_str(path_name, ft_itoa(get_last_file()));
	fd_tmp = open(path_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_tmp < 0)
		return (-1);
	heredoc->word = path_name;
	heredoc->operand = INPUT;
	return (fd_tmp);
}

static void	handle_heredoc(t_flow *heredoc)
{
	int		fd_tmp;
	char	*delimiter;
	char	*input_hd;

	if ((!heredoc || !heredoc->word) && heredoc->operand != HEREDOC)
		return ;
	input_hd = NULL;
	delimiter = heredoc->word;
	fd_tmp = create_file_tmp(heredoc);
	if (fd_tmp < 0)
		return ;
	while (get_sigint_hd())
	{
		signal(SIGINT, signal_heredoc);
		input_hd = readline("heredoc► ");
		if (!input_hd)
		{
			print_warning_delimiter(delimiter);
			break ;
		}
		if (!ft_strcmp(delimiter, input_hd))
		{
			free(input_hd);
			break ;
		}
		write_heredoc(input_hd, fd_tmp, heredoc->expandable);
		free(input_hd);
	}
	close(fd_tmp);
}

void	parse_heredoc(t_tokens *tokens)
{
	t_flow	*flows;

	if (!tokens)
		return ;
	flows = NULL;
	while (tokens != NULL && get_sigint_hd())
	{
		flows = tokens->token_flow;
		while (flows != NULL && get_sigint_hd())
		{
			if (flows->operand == HEREDOC)
				handle_heredoc(flows);
			flows = flows->next_flow;
		}
		tokens = tokens->next;
	}
	if (get_stdin_dup() > 0)
	{
		dup2(get_stdin_dup(), STDIN_FILENO);
		close(get_stdin_dup());
		set_stdin_dup(-1);
	}
}
