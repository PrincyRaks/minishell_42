/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:43:57 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/07 14:58:43 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_folder_tmp(char **str_folder)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("Error path");
		*str_folder = NULL;
		return ;
	}
	*str_folder = ft_strjoin(ft_strdup(cwd), "/");
}

static int	create_file_tmp(t_flow *heredoc)
{
	int			fd_tmp;
	char		*path_name;
	static int	num_file = -1;

	set_folder_tmp(&path_name);
	if (!path_name)
		return (-1);
	num_file++;
	set_num_file(num_file);
	path_name = concat_str(path_name, ft_itoa(num_file));
	fd_tmp = open(path_name, O_CREAT | O_WRONLY);
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
	while (1)
	{
		// implements signal here !
		// signal(SIGINT, stopheredoc);
		input_hd = readline("heredoc► ");
		if (!input_hd)
		{
			print_warning_delimiter(delimiter);
			break ;
		}
		if (!ft_strcmp(delimiter, input_hd))
			break ;
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
	while (tokens != NULL)
	{
		flows = tokens->token_flow;
		while (flows != NULL)
		{
			if (flows->operand == HEREDOC)
				handle_heredoc(flows);
			flows = flows->next_flow;
		}
		tokens = tokens->next;
	}
}
