/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:02 by rrakotos          #+#    #+#             */
/*   Updated: 2024/12/16 11:57:12 by mrazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <limits.h>
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
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>



# define SYNTAX_ERROR 1

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
typedef struct s_tokens
{
	t_cmd				*token_cmd;
	t_arg				*token_arg;
	struct s_tokens		*next;
}						t_tokens;

// Shell_loop
void					handle_command(t_tokens *data_cmd);
void					shell_loop(void);

// Executor
void					free_array(char **array);
bool	is_only_dots(const char *command);
char					*find_executable(char *command);

// Parser
// quotes
t_tokens				**store_instruction(char *input);
char					*parse_input(char **start_quotes);
char					*remove_onequotes(char **start_quotes);
char					*remove_doubquotes(char **start_quotes);
t_tokens				**store_instruction(char *input);
void					addback_arg(t_arg **first_arg, char *str_arg);
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
char    *concat_str(char *prev_result, char *handle);

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
void	clean_node_env(t_data_env *node);

// utils
char					*join_onespace(char *s1, char *s2);
int						count_tab(char **tab);

// Builtins
int						ft_cd(t_tokens *tokens);
int						ft_pwd(void);
int						ft_exit(t_tokens *tokens);
void					ft_env(void);
void					ft_echo(t_tokens *tokens);
int						ft_export(t_tokens *tokens);
int ft_unset(t_tokens *tokens);
int						is_builtin(char *cmd);

// Builtin utils
int						is_numeric(const char *str);
int						ft_strcmp(char *s1, char *s2);
void					execute_builtin(t_tokens *tokens);

// Pipe
void execute_single_command(t_tokens *token);
void execute_pipeline(t_tokens *tokens);

// Signals
void	handle_sigint(int signum);
void	setup_signals(void);
void	check_eof(char *input);



#endif
