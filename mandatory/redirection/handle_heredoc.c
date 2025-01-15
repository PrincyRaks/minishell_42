/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:43:57 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/14 11:11:38 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_file_tmp(t_flow *heredoc)
{
	int		fd_tmp;
	char	*path_name;
	int		next_file;

	set_folder_tmp(&path_name);
	if (!path_name)
		return (-1);
	next_file = get_last_file();
	next_file++;
	set_num_file(next_file);
	path_name = concat_str(path_name, concat_str(ft_strdup("."),
				ft_itoa(get_last_file())));
	fd_tmp = open(path_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_tmp < 0)
		return (-1);
	heredoc->word = path_name;
	heredoc->operand = INPUT;
	return (fd_tmp);
}

int	handle_delimiter(char *input_hd, char *delimiter)
{
	if (!input_hd)
	{
		print_warning_delimiter(delimiter);
		return (0);
	}
	if (!ft_strcmp(delimiter, input_hd))
	{
		free(input_hd);
		return (0);
	}
	return (1);
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
	while (get_sigint())
	{
		signal(SIGINT, stop_instruction);
		input_hd = readline("heredoc► ");
		if (!handle_delimiter(input_hd, delimiter))
			break ;
		write_heredoc(input_hd, fd_tmp, heredoc->expandable);
		free(input_hd);
	}
	free(delimiter);
	close(fd_tmp);
}

void	parse_heredoc(t_tokens *tokens)
{
	t_flow	*flows;

	if (!tokens)
		return ;
	flows = NULL;
	while (tokens != NULL && get_sigint())
	{
		flows = tokens->token_flow;
		while (flows != NULL && get_sigint())
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
