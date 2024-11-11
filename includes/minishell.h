/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:02 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/11 13:35:09 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char			*cmd_str;
	int is_cmd; //  0 is true & -1 is false
}					t_cmd;

typedef struct s_args
{
	char *arg_cmd; // -options and argument of cmd
	struct s_args	*next_arg;
}					t_arg;

// typedef struct s_operator
// {
// 	char	*operator;
// }			t_operator;

typedef struct s_tokens
{
	t_cmd			*token_cmd;
	t_arg			*token_arg;
	// t_operator token_o;
	// t_tokens	*next;  //cmd next of | (pipes)
}					t_tokens;

void				shell_loop(char **envp);

// Executor
char				**get_path(char **envp);
void				free_array(char **array);
char				*find_executable(char *command, char **envp);

// Parser
// quotes
// char		*concat(char *s1, char *s2);
void				store_token(char *input);
char				*trim_quotes(char **start_quotes);
char				*remove_onequotes(char **start_quotes);
char				*remove_doubquotes(char **start_quotes);

// utils

#endif