/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:32:20 by mrazanad          #+#    #+#             */
/*   Updated: 2024/12/03 10:26:02 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_redirections(t_arg *args)
{
    int fd;
    t_arg *current;

    current = args;
    while (current)
    {
        if (current->errnum == O_RDONLY)
            fd = open(current->arg_str, O_RDONLY);
        else if (current->errnum == (O_WRONLY | O_CREAT | O_APPEND))
            fd = open(current->arg_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else if (current->errnum == (O_WRONLY | O_CREAT | O_TRUNC))
            fd = open(current->arg_str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            return(-1);
        if (fd == -1)
        {
            perror(current->arg_str);
            return (-1);
        }
        if (current->arg_str == O_RDONLY)
            dup2(fd, STDIN_FILENO);
        else
            dup2(fd, STDOUT_FILENO);
        close(fd);
        current = current->next_arg;
    }
    return (0);
}
