/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:12:44 by rrakotos          #+#    #+#             */
/*   Updated: 2025/01/06 14:43:47 by rrakotos         ###   ########.fr       */
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
