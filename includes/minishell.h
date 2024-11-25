/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:02 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/25 08:46:08 by mrazanad         ###   ########.fr       */
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
# include <stddef.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <fcntl.h>


// Redirections
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
}	t_redir;

// typedef struct s_cmd
// {
// 	char			*cmd_str;
// 	int is_cmd; //  0 is true & -1 is false
// }					t_cmd;

// typedef struct s_arg
// {
// 	char *arg_cmd; // -options and argument of cmd
// 	struct s_arg	*next_arg;
// }					t_arg;

// // typedef struct s_operator
// // {
// // 	char	*operator;
// // }			t_operator;

// typedef struct s_tokens
// {
// 	t_cmd			*token_cmd;
// 	t_arg			*token_arg;
// 	// t_operator token_o;
// 	struct s_tokens *next; // cmd next of | (pipes)
// }					t_tokens;

// Shell_loop
int is_builtin(char *cmd);
void handle_command(char *input, char **paths, char **envp);
void execute_command(char **args, char **paths, t_redir *redirs, char **envp);
void				shell_loop(char **envp);

// Executor
char				**get_path(char **envp);
void				free_array(char **array);
char				*find_executable(char *command, char **envp);

// Parser
// quotes
// char		*concat(char *s1, char *s2);
// t_tokens			*store_token(char *input);
// char				*trim_quotes(char **start_quotes);
// char				*remove_onequotes(char **start_quotes);
// char				*remove_doubquotes(char **start_quotes);
// void				addback_arg(t_arg **first_arg, char *str_arg);
// t_tokens			*create_node(void);
// void				addback_token(t_tokens **first_token, t_tokens *token);
// int					count_token(t_tokens *lst);

// utils

// Builtins
int ft_cd(char **args);
int ft_pwd(void);
int ft_exit(char **args);

// Builtin utils
int is_numeric(const char *str);
int	ft_strcmp(char *s1, char *s2);
void execute_builtin(char **args);

// Redirections Utils
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
int handle_heredoc(char **args, int *i, t_redir **redirs);

#endif