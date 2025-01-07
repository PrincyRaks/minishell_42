/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:00 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/07 14:23:20 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getpath_tmp(char *file)
{
	char	*res;
	char	cwd[PATH_MAX];

	res = ft_calloc(1, sizeof(char));
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return (NULL);
	}
	res = ft_strjoin(ft_strdup(cwd), "/");
	res = ft_strjoin(res, file);
	if (access(res, F_OK) != 0)
	{
		free(res);
		perror("access");
		return (NULL);
	}
	return (res);
}

void    delete_file_tmp(int last_num)
{
	char	*num_file;

	num_file = NULL;
	while (last_num > -1)
	{
		num_file = ft_itoa(last_num);
		unlink(num_file);
		free(num_file);
		last_num--;
	}
}

void	print_warning_delimiter(char *str)
{
	printf("warning: here-document delimited \
    by end-of-file (wanted `%s')\n", str);
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

//  !!! check signal ctrl + D and display warning !!!
// int	open_heredoc(t_flow *flow)
// {
// 	int		fd_tmp;
// 	char	*delimiter;
// 	char	*input_hd;

// 	if ((!flow || !flow->word) && flow->operand != HEREDOC)
// 		return (-1);
// 	input_hd = NULL;
// 	delimiter = flow->word;
// 	fd_tmp = create_file_tmp();
//     printf("fd: %d\n", fd_tmp);
// 	while (fd_tmp >= 0)
// 	{
// 		input_hd = readline("heredoc► ");
// 		if (!input_hd || !ft_strcmp(delimiter, input_hd))
// 			break ;
// 		write_heredoc(input_hd, fd_tmp, flow->expandable);
// 		ft_putchar_fd('\n', fd_tmp);
// 		free(input_hd);
// 	}
// 	close(fd_tmp);
// 	set_fd_heredoc(fd_tmp);
// 	return (fd_tmp);
// }
