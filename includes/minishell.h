/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:02 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/14 15:51:08 by rrakotos         ###   ########.fr       */
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

typedef struct s_data_env
{
	char				*key;
	char				*value;
	struct s_data_env	*next;
}						t_data_env;

typedef struct s_cmd
{
	char				*cmd_str;
	int is_cmd; //  0 is true & -1 is false
}						t_cmd;

typedef struct s_arg
{
	char *arg_cmd; // -options and argument of cmd
	int is_expand; // if 0 not expand if 1 is expandable 	->chage value of arg_cmd if 1
	struct s_arg		*next_arg;
}						t_arg;

// typedef struct s_operator
// {
// 	// enum type
// 	int		order;

// }			t_operator;

typedef struct s_tokens
{
	t_cmd				*token_cmd;
	t_arg				*token_arg;
	// t_operator token_o;
	struct s_tokens *next; // cmd next of | (pipes)
}						t_tokens;

void					shell_loop(char **envp);

// Executor
void					free_array(char **array);
char					*find_executable(char *command);

// Parser
// quotes
// char		*concat(char *s1, char *s2);
t_tokens				**store_token(char *input);
char					*trim_quotes(char **start_quotes);
char					*remove_onequotes(char **start_quotes);
char					*remove_doubquotes(char **start_quotes);
void					addback_arg(t_arg **first_arg, char *str_arg);
t_tokens				*new_token(void);
void					addback_token(t_tokens **first_token, t_tokens *token);
int						count_token(t_tokens *lst);
t_arg					*new_arg(void);
t_cmd	*new_cmd(void);
char	*expand(char **var);

// env
void					addback_env(t_data_env **lst, t_data_env *node);
t_data_env				*hash_env(char *data);
void					dup_env(char **env);
void					clean_env(t_data_env **lst);
void					set_data_env(t_data_env *value);
t_data_env				*get_data_env(void);
t_data_env				*ft_getenv(char *var);

// utils

// Builtins
int						ft_cd(char **args);
int						ft_pwd(void);
int						ft_exit(char **args);
void					ft_env(void);

// Builtin utils
int						is_numeric(const char *str);
int						ft_strcmp(char *s1, char *s2);
void					execute_builtin(char **args);

#endif