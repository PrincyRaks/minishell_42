/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:43:07 by mrazanad          #+#    #+#             */
/*   Updated: 2024/11/25 08:25:05 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_arraylen(char **array)
{
	size_t	len;

	len = 0;
	if (!array)
		return (0);
	while (array[len])
		len++;
	return (len);
}

int	is_redirection_operator(char *arg)
{
	return (ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, ">") == 0
		|| ft_strcmp(arg, ">>") == 0 || ft_strcmp(arg, "<<") == 0);
}

t_redir_type	get_redirection_type(char *operator)
{
	if (ft_strcmp(operator, "<") == 0)
		return (REDIR_INPUT);
	if (ft_strcmp(operator, ">>") == 0)
		return (REDIR_APPEND);
	if (ft_strcmp(operator, "<<") == 0)
		return (REDIR_HEREDOC);
	return (REDIR_OUTPUT);
}

int	handle_redirection(char **args, int *i, t_redir **redirs)
{
	t_redir_type	type;

	if (!args[*i + 1])
	{
		printf("syntax error near unexpected token `%s`\n", args[*i]);
		return (0);
	}
	if (ft_strcmp(args[*i], "<<") == 0)
		return (handle_heredoc(args, i, redirs));
	type = get_redirection_type(args[*i]);
	add_redir(redirs, create_redir(args[*i + 1], type));
	*i += 2;
	return (1);
}

void	process_arguments(char **args, char **filtered_args, t_redir **redirs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (is_redirection_operator(args[i]))
		{
			if (!handle_redirection(args, &i, redirs))
			{
				free_array(filtered_args);
				return ;
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
