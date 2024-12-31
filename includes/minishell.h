/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:02 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/31 10:55:13 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define SYNTAX_ERROR 1
# define PROMPT "👾$ "


typedef enum e_errnum
{
	DEFAULT,
	UNQUOTES,
	ERRFLOW,
	AMBIGUOUS, 	
	ERRPIPE,
}						t_errnum;

typedef enum e_operator
{
	NOTOP,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
	VOIDTOKEN,
}						t_operator;

typedef struct s_data_env
{
	char				*key;
	char				*value;
	struct s_data_env	*next;
}						t_data_env;

typedef struct s_cmd
{
	char				*cmd_str;
	t_operator			operand;
	t_errnum			errnum;
}						t_cmd;

typedef struct s_arg
{
	char				*arg_str;
	t_errnum			errnum;
	t_operator			operand;
	struct s_arg		*next_arg;
}						t_arg;

// redirection
typedef struct s_flow
{
	char				*word;
	t_operator			operand;
	struct s_flow		*next_flow;
}						t_flow;

typedef struct s_tokens
{
	t_cmd				*token_cmd;
	t_arg				*token_arg;
	t_flow				*token_flow;
	t_errnum			errnum;
	struct s_tokens		*next;
}						t_tokens;

// Shell_loop
void					shell_loop(void);

// Handle Command
void					handle_child_process(char *executable,
							t_tokens *data_cmd);
void					handle_parent_process(pid_t pid);
void					execute_external_command(char *executable,
							t_tokens *data_cmd);
int						is_invalid_command(t_tokens *data_cmd);
void					handle_external_command(t_tokens *data_cmd);
void					handle_command(t_tokens *data_cmd);

// Executor
void					free_array(char **array);
bool					is_only_dots(const char *command);
char					*find_executable(char *command);

// Parser
// quotes
t_tokens				**store_instruction(char *input);
char					*parse_input(t_tokens *token, char **input,
							int *mode_add);
char					*remove_onequotes(char **start_quotes);
char					*remove_doubquotes(char **qts, int is_expand);
t_tokens				**store_instruction(char *input);
void					addback_arg(t_arg **first_arg, t_arg *node_arg);
t_tokens				*new_token(void);
void					addback_token(t_tokens **first_token, t_tokens *token);
int						count_token(t_tokens *lst);
t_arg					*new_arg(void);
t_cmd					*new_cmd(void);
char					*handle_dollar(char **var);
void					clean_cmd(t_cmd *cmd);
void					clean_args(t_arg **lst);
void					clean_tokens(t_tokens **lst);
int						count_arg(t_arg *node);
char					**array_tokens(t_tokens *token);
char					*concat_str(char *prev_result, char *handle);
t_arg					*last_arg(t_arg *arg);
int						count_flow(t_flow *node);
t_flow					*new_flow(void);
t_flow					*last_flow(t_flow *flows);
void					addback_flow(t_flow **first_flow, t_flow *node_flow);
void					clean_flows(t_flow **lst);
char					*handle_onequotes(char **qts, char **result,
							t_tokens *token);
char					*handle_doubquotes(char **qts, char **result,
							t_tokens *token, int is_expand);
void					handle_var(char **input, char **res, t_tokens *token,
							int *mode);
int						handle_flow(t_tokens *token, char **input,
							int *mode_add, int *is_expand);
int						count_dollar(char *dollar);
char					*dupnb_dollar(int nb_dollar);
int						valid_char(char c);
int						valid_token(t_tokens *token, char char_input);
void					append_char(char **input, char **result);
int						valid_redir(char c);

// env
void					addback_env(t_data_env **lst, t_data_env *node);
void					dup_env(char **envp);
void					clean_env(t_data_env **lst);
void					set_data_env(t_data_env *value);
t_data_env				*get_data_env(void);
t_data_env				*ft_getenv(char *var);
int						count_data_env(t_data_env *node);
char					**get_tabenv(void);
void					load_data_export(void);
char					**get_tabkeys(void);
char					**get_data_export(void);
void					set_data_export(char **value);
t_data_env				*hash_env(char *data);
void					clean_node_env(t_data_env *node);
void					clear_export_env(void);

// utils
char					*join_onespace(char *s1, char *s2);
int						count_tab(char **tab);
t_errnum				check_errnum(t_tokens *token);
void					print_errnum(t_errnum numerr);

// Builtins
int						ft_cd(t_tokens *tokens);
int						ft_pwd(void);
int						ft_exit(t_tokens *tokens);
void					ft_env(void);
void					ft_echo(t_tokens *tokens);
int						ft_export(t_tokens *tokens);
int						ft_unset(t_tokens *tokens);
int						is_builtin(char *cmd);

// Builtin utils
int						is_numeric(const char *str);
int						ft_strcmp(char *s1, char *s2);
void					execute_builtin(t_tokens *tokens, int nb);

// Pipe Utils
void					setup_pipe(int prev_fd, int pipe_fd[2],
							t_tokens *tokens);
void					wait_for_children(void);
void					handle_child(int prev_fd, int pipe_fd[2],
							t_tokens *tokens);
int						handle_parent(int prev_fd, int pipe_fd[2],
							t_tokens *tokens);
void					exit_perror(char *message);

// Pipe
void					execute_single_command(t_tokens *token);
void					execute_pipeline(t_tokens *tokens);
void 					set_signals_pipe(void);

// Redirections
int						check_errflow(t_flow *flow);
// void    execute_redirection(t_tokens *token);
int						open_redirection_file(t_flow *redir);
int						apply_redirection(t_tokens *token);
void					restore_stdio(int saved_stdin, int saved_stdout);

// Signals
void					signal_reset_prompt(int signo);
void					ignore_sigquit(void);
void					set_signals_interactive(void);
void					signal_print_newline(int signal);
void					set_signals_noninteractive(void);

#endif
