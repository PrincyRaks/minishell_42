/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:02 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/26 14:06:40 by mrazanad         ###   ########.fr       */
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
#include <stddef.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>
#include <fcntl.h>

/* // Redirections
typedef enum e_redir_type
{
	REDIR_INPUT, // "<"
	REDIR_OUTPUT, // ">"
	REDIR_APPEND, // ">>"
	REDIR_HEREDOC // "<<"
}	t_redir_type;

typedef struct s_redir
{
	int heredoc_fd;
	char *file_name;
	t_redir_type type;
	struct s_redir *next;
}	t_redir; */

typedef enum e_errnum
{
	DEFAULT = 0,
	NOTCMD = -1,
	UNQUOTES = -2
}						t_errnum;

typedef struct s_data_env
{
	char				*key;
	char				*value;
	struct s_data_env	*next;
}						t_data_env;

typedef struct s_cmd
{
	char				*cmd_str;
	int					errnum;
}						t_cmd;

typedef struct s_arg
{
	char *arg_str; // -options and argument of cmd
	int					errnum;
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

// Shell_loop
void					shell_loop(void);
void					handle_command(t_tokens *data_cmd);

// Executor
void					free_array(char **array);
char					*find_executable(char *command);
// fanampiana
char	**array_tokens(t_tokens *token);


// Parser
// quotes
t_tokens				**store_token(char *input);
char					*trim_quotes(char **start_quotes);
char					*remove_onequotes(char **start_quotes);
char					*remove_doubquotes(char **start_quotes);
void					addback_arg(t_arg **first_arg, char *str_arg);
t_tokens				*new_token(void);
void					addback_token(t_tokens **first_token, t_tokens *token);
int						count_token(t_tokens *lst);
t_arg					*new_arg(void);
t_cmd					*new_cmd(void);
char					*handle_dollar(char **var);
char					*expand(char **var);
void					clean_cmd(t_cmd *cmd);
void					clean_args(t_arg **lst);
void					clean_tokens(t_tokens **lst);
int						count_arg(t_arg *node);

// env
void					addback_env(t_data_env **lst, t_data_env *node);
void					dup_env(char **env);
void					clean_env(t_data_env **lst);
void					set_data_env(t_data_env *value);
t_data_env				*get_data_env(void);
t_data_env				*ft_getenv(char *var);
int						count_data_env(t_data_env *node);
char					**get_tabenv(void);

// utils
// char		*concat(char *s1, char *s2);

// Builtins
int						ft_cd(t_tokens *tokens);
int						ft_pwd(void);
int						ft_exit(t_tokens *tokens);
void					ft_env(void);
int						is_builtin(char *cmd);

// Builtin utils
int						is_numeric(const char *str);
int						ft_strcmp(char *s1, char *s2);
void					execute_builtin(t_tokens *tokens);

/* // Redirections Utils
void process_arguments(char **args, char **filtered_args, t_redir **redirs);
int is_redirection_operator(char *arg);
int handle_redirection(char **args, int *i, t_redir **redirs);
t_redir_type get_redirection_type(char *operator);

// Redirections
char **parse_redirections(char *input, t_redir **redirs);
int open_redirection_file(t_redir *redir);
int apply_redirection(t_redir *redir);
t_redir *create_redir(char *file_name, t_redir_type type);
void add_redir(t_redir **head, t_redir *new_redir);
void free_redirs(t_redir *redirs);
size_t ft_arraylen(char **array);

// Heredoc
t_redir *create_redir_from_fd(int fd, t_redir_type type);
char *read_heredoc_line(void);
void process_heredoc(int pipe_fd[2], char *delim);
int handle_heredoc(char **args, int *i, t_redir **redirs); */

// Pipe
void execute_single_command(t_tokens *token);
void execute_pipeline(t_tokens *tokens);
void free_tokens(t_tokens **tokens);

#endif