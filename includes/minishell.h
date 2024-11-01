/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:02 by rrakotos          #+#    #+#             */
/*   Updated: 2024/11/01 16:16:41 by rrakotos         ###   ########.fr       */
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

void	shell_loop(char **envp);

// Executor
char	**get_path(char **envp);
char	*find_executable(char *command, char **envp);

// Parser
// quotes 
char	*handle_quotes(char *input);
char	*concat(char *s1, char *s2);
char	*trim_doubquotes(char *str);

void	free_table(void **tab);
int		count_char(char *str, int c);
int		count_tab(char **tab);

#endif