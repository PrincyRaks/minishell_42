/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:41:00 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/24 10:45:39 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_warning_delimiter(char *str)
{
    printf("warning: here-document \
    delimited by end-of-file (wanted `%s')\n", str);
}

static void    set_folder_tmp(char **str_folder)
{
    char    cwd[PATH_MAX];
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("pwd");
        *str_folder = NULL;
        return ;
    }
    *str_folder = ft_strjoin(ft_strdup(cwd), "/");
}

//  !!! check signal ctrl + D and display warning !!!
void    open_heredoc(t_flow  *flow)
{
    char    *delimiter;
    char    *input_hd;
    int     fd_tmp;
    // int     is_expand;
    // static int  file_tmp;
    char *path_name;

    if ((!flow || !flow->word) && flow->operand != HEREDOC)
        return ;
    set_folder_tmp(&path_name);
    if (!path_name)
        return ;
    path_name = ft_strjoin(path_name, "1");
    input_hd = NULL;
    delimiter = flow->word;
    // is_expand = flow->expandable;
    // file_tmp = 1;
    fd_tmp = open(path_name , O_CREAT | O_WRONLY | O_APPEND);
    printf("fd: %d et path: %s\n", fd_tmp, path_name);
    while (fd_tmp >= 0 && (!input_hd || ft_strcmp(delimiter, input_hd) != 0))
    {
        input_hd = readline("heredoc► ");
        if (!input_hd)
            return ;
        if (!ft_strcmp(delimiter, input_hd))
            break ;
        // handle quotes and var
        ft_putstr_fd(input_hd, fd_tmp);
        ft_putchar_fd('\n', fd_tmp);

    }
}
