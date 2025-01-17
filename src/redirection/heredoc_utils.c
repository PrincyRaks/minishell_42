/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:00 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/14 10:57:42 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_file_tmp(int last_num)
{
	char	*num_file;

	num_file = NULL;
	while (last_num > -1)
	{
		num_file = concat_str(ft_strdup("."), ft_itoa(last_num));
		unlink(num_file);
		free(num_file);
		last_num--;
	}
}

void	print_warning_delimiter(char *str)
{
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `",
		STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putendl_fd("')", STDOUT_FILENO);
}

void	write_specific_heredoc(char **input, int fd_tmp, int expandable)
{
	if (**input == '$' && expandable && ((*((*input) + 1)) == '"' || *((*input)
				+ 1) == '\''))
	{
		while (**input != '$' && **input != '\0' && **input != '"'
			&& **input == '\'')
		{
			ft_putchar_fd(**input, fd_tmp);
			(*input)++;
		}
	}
}

void	write_heredoc(char *input, int fd_tmp, int expandable)
{
	char	*expand;

	expand = NULL;
	while (*input)
	{
		write_specific_heredoc(&input, fd_tmp, expandable);
		if (*input == '$' && expandable)
		{
			expand = handle_dollar(&input);
			if (expand != NULL)
			{
				ft_putstr_fd(expand, fd_tmp);
				free(expand);
			}
		}
		if ((*input != '$' && *input != '\0') || !expandable)
		{
			ft_putchar_fd(*input, fd_tmp);
			input++;
		}
	}
	ft_putchar_fd('\n', fd_tmp);
}

void	set_folder_tmp(char **str_folder)
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
