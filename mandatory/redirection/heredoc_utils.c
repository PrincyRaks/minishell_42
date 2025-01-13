/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:00 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/13 15:07:31 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_file_tmp(int last_num)
{
	char	*num_file;

	num_file = NULL;
	while (last_num > -1)
	{
		num_file = ft_strjoin(ft_strdup("."), ft_itoa(last_num));
		unlink(num_file);
		free(num_file);
		last_num--;
	}
}

void	print_warning_delimiter(char *str)
{
	printf("warning: here-document delimited by end-of-file (wanted `%s')\n",
		str);
}

void	write_heredoc(char *input, int fd_tmp, int expandable)
{
	char	*expand;

	expand = NULL;
	while (*input)
	{
		if (*input == '$' && expandable && (*(input + 1) == '"' || *(input
					+ 1) == '\''))
		{
			while (*input != '$' && *input != '\0' && *input != '"'
				&& *input == '\'')
			{
				ft_putchar_fd(*input, fd_tmp);
				input++;
			}
		}
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
