/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:00 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/06 16:01:48 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_warning_delimiter(char *str)
{
	printf("warning: here-document delimited \
    by end-of-file (wanted `%s')\n", str);
}

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
}

int	create_file_tmp(void)
{
	int		fd_tmp;
	int		fd_closed;
	char	*path_name;
    static int num_file = -1;

	set_folder_tmp(&path_name);
	if (!path_name)
		return (-1);
	fd_closed = get_last_fd_heredoc();
	if (fd_closed >= 0)
	{
		// misy ts mety eto eee !!!!!
		printf("misy ts mety eto\n");
		dup2(get_stdin_dup(), STDIN_FILENO);
		close(fd_closed);
	}
	num_file++;
	set_num_file(num_file);
	path_name = concat_str(path_name, ft_itoa(num_file));
	printf("path tmp: %s\n", path_name);
	fd_tmp = open(path_name, O_CREAT | O_WRONLY | O_TRUNC);
	return (fd_tmp);
}

//  !!! check signal ctrl + D and display warning !!!
int	open_heredoc(t_flow *flow)
{
	int		fd_tmp;
	char	*delimiter;
	char	*input_hd;

	if ((!flow || !flow->word) && flow->operand != HEREDOC)
		return (-1);
	input_hd = NULL;
	delimiter = flow->word;
	fd_tmp = create_file_tmp();
    printf("fd: %d\n", fd_tmp);
	while (fd_tmp >= 0)
	{
		input_hd = readline("heredoc► ");
		if (!input_hd || !ft_strcmp(delimiter, input_hd))
			break ;
		write_heredoc(input_hd, fd_tmp, flow->expandable);
		ft_putchar_fd('\n', fd_tmp);
		free(input_hd);
	}
	close(fd_tmp);
	set_fd_heredoc(fd_tmp);
	return (fd_tmp);
}
