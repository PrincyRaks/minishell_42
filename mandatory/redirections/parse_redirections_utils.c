/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:43:07 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/22 14:08:58 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

size_t ft_arraylen(char **array)
{
    size_t len = 0;

    if (!array)
        return (0);
    while (array[len])
        len++;
    return (len);
}

void process_arguments(char **args, char **filtered_args, t_redir **redirs)
{
    int i = 0;
    int j = 0;

    while (args[i])
    {
        if (is_redirection_operator(args[i]))
        {
            if (!handle_redirection(args, &i, redirs))
            {
                free_array(filtered_args);
                return;
            }
        }
        else
        {
            filtered_args[j++] = strdup(args[i]);
            i++;
        }
    }
    filtered_args[j] = NULL;
}

int is_redirection_operator(char *arg)
{
    return (ft_strcmp(arg, "<") == 0 || 
            ft_strcmp(arg, ">") == 0 || 
            ft_strcmp(arg, ">>") == 0);
}

int handle_redirection(char **args, int *i, t_redir **redirs)
{
    t_redir_type type;

    if (!args[*i + 1])
    {
        printf("syntax error near unexpected token `%s`\n", args[*i]);
        return (0);
    }
    type = get_redirection_type(args[*i]);
    add_redir(redirs, create_redir(args[*i + 1], type));
    *i += 2;
    return (1);
}

t_redir_type get_redirection_type(char *operator)
{
    if (ft_strcmp(operator, "<") == 0)
        return (REDIR_INPUT);
    if (ft_strcmp(operator, ">>") == 0)
        return (REDIR_APPEND);
    return (REDIR_OUTPUT);
}

