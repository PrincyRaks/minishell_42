/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrazanad <mrazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:02 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/11 14:15:36 by mrazanad         ###   ########.fr       */
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
	char	*cmd_str;
	int		is_cmd;
}			t_cmd;

typedef struct s_args
{
	char	**args_cmd;
}			t_args;

typedef struct s_operator
{
	char	*operator;
}			t_operator;

typedef struct s_tokens
{
	t_cmd	token_c;
	t_args	token_a;
	t_operator token_o;
}			t_tokens;

void		shell_loop(char **envp);

// Executor
char	**get_path(char **envp);
void	free_array(char **array);
char	*find_executable(char *command, char **envp);


// Parser
// quotes
char	*concat(char *s1, char *s2);
int	what_quotes(char *str);
char	*trim_simplequotes(char *str);
char	*trim_doubquotes(char *str);
char	*handle_quotes(char *input);

// utils
void	free_table(void **tab);
int		count_char(char *str, int c);
int		count_tab(char **tab);

// Builtins
int ft_cd(char **args);
int ft_pwd(void);
int ft_exit(char **args);

// Builtin utils
int is_numeric(const char *str);
int	ft_strcmp(char *s1, char *s2);
void execute_builtin(char **args);

#endif