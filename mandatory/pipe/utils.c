/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakotos <rrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:12:14 by mrazanad          #+#    #+#             */
/*   Updated: 2025/01/11 12:18:49 by rrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*get_prev_token(t_tokens *head, t_tokens *current)
{
	t_tokens	*prev;
	t_tokens	*temp;

	prev = NULL;
	temp = head;
	if (current == head)
		return (NULL);
	while (temp && temp != current)
	{
		prev = temp;
		temp = temp->next;
	}
	return (prev);
}

void	setup_child_process(t_tokens *tokens, t_tokens *current, int prev_fd,
		int *pipe_fd)
{
	(void)tokens;
	set_signals_noninteractive();
	// printf("\nDEBUG [Child %d]: Command: %s\n", getpid(), 
	// 	current->token_cmd ? current->token_cmd->cmd_str : "NULL");
	// printf("DEBUG [Child %d]: FDs - prev_fd=%d, pipe[0]=%d, pipe[1]=%d\n", 
	// 	getpid(), prev_fd, pipe_fd[0], pipe_fd[1]);

	if (prev_fd != -1)
	{
		// printf("DEBUG [Child %d]: Setting stdin from prev_fd %d\n", getpid(), prev_fd);
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			perror("dup2 prev_fd");
		close(prev_fd);
	}

	if (current->next)
	{
		// printf("DEBUG [Child %d]: Setting stdout to pipe_fd[1] %d\n", getpid(), pipe_fd[1]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2 pipe_fd");
	}

	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);

	if (current->token_flow)
	{
		// printf("DEBUG [Child %d]: Applying redirections\n", getpid());
		apply_redirection(current);
	}
	execute_single_command(current);
}

// int	check_command(t_tokens *current)
// {
// 	if (!current->token_cmd && current->token_flow)
// 		return (1);

// 	if (!current->token_cmd || !current->token_cmd->cmd_str
// 		|| (!is_builtin(current->token_cmd->cmd_str)
// 			&& !find_executable(current->token_cmd->cmd_str)))
// 	{
// 		if (!current->token_flow)
// 		{
// 			if (current->token_cmd != NULL && current->token_cmd->cmd_str != NULL 
// 				&& (current->token_cmd->cmd_str[0] == '/' || current->token_cmd->cmd_str[0] == '.'))
// 			{
// 				if (access(current->token_cmd->cmd_str, F_OK) != 0)
// 				{
// 					ft_putstr_fd(" : ", 2);
// 					ft_putstr_fd(current->token_cmd->cmd_str, 2);
// 					ft_putstr_fd(": No such file or directory\n", 2);
// 				}
// 				else if (access(current->token_cmd->cmd_str, X_OK) != 0)
// 				{
// 					ft_putstr_fd(" : ", 2);
// 					ft_putstr_fd(current->token_cmd->cmd_str, 2);
// 					ft_putstr_fd(": Permission denied\n", 2);
// 				}
// 			}
// 			else
// 			{
// 				ft_putstr_fd(current->token_cmd->cmd_str, 2);
// 				ft_putstr_fd(" : command not found\n", 2);
// 			}
// 		}
// 		return (0);
// 	}
// 	return (1);
// }

int check_command(t_tokens *current)
{
    t_tokens *temp = current;
    t_tokens *cmd_token = NULL;
    
    while (temp) 
	{
        if (temp->token_cmd && temp->token_cmd->cmd_str)
		{
            cmd_token = temp;
            break;
        }
        temp = temp->next;
    }
    // if (!cmd_token) {
    //     ft_putstr_fd("syntax error: command not found\n", 2);
    //     return (0);
    // }
    if (!is_builtin(cmd_token->token_cmd->cmd_str) 
        && !find_executable(cmd_token->token_cmd->cmd_str))
    {
        if (cmd_token->token_cmd->cmd_str[0] == '/' 
            || cmd_token->token_cmd->cmd_str[0] == '.') 
        {
            if (access(cmd_token->token_cmd->cmd_str, F_OK) != 0) {
                ft_putstr_fd(cmd_token->token_cmd->cmd_str, 2);
                ft_putstr_fd(": No such file or directory\n", 2);
				set_status(2);
            }
            else if (access(cmd_token->token_cmd->cmd_str, X_OK) != 0) {
                ft_putstr_fd(cmd_token->token_cmd->cmd_str, 2);
                ft_putstr_fd(": Permission denied\n", 2);
				set_status(1);
            }
        }
        else {
            ft_putstr_fd(cmd_token->token_cmd->cmd_str, 2);
            ft_putstr_fd(": command not found\n", 2);
			set_status(127);
        }
        return (0);
    }
    return (1);
}


void	handle_pipe_fds(t_tokens *tokens, t_tokens *current, int *prev_fd,
		int *pipe_fd)
{
	(void)tokens;
	// printf("\nDEBUG [Parent]: Handling FDs for command: %s\n", 
	// 	current->token_cmd ? current->token_cmd->cmd_str : "NULL");

	if (*prev_fd != -1)
	{
		// printf("DEBUG [Parent]: Closing prev_fd %d\n", *prev_fd);
		close(*prev_fd);
	}

	if (current->next)
	{
		// printf("DEBUG [Parent]: Closing pipe write end %d\n", pipe_fd[1]);
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
		// printf("DEBUG [Parent]: Saving pipe read end %d for next command\n", pipe_fd[0]);
	}
	else
	{
		// printf("DEBUG [Parent]: Last command, closing both pipe ends\n");
		if (pipe_fd[0] != -1)
			close(pipe_fd[0]);
		if (pipe_fd[1] != -1)
			close(pipe_fd[1]);
		*prev_fd = -1;
	}
}

void	execute_command(t_tokens *tokens, t_tokens *current, int *prev_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int	status = 0;

	if (current->next)
	{
		// printf("DEBUG [Parent]: Creating pipe for command: %s\n",
		// 	current->token_cmd ? current->token_cmd->cmd_str : "NULL");
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			set_signals_interactive();
			exit_perror("pipe");
		}
		// printf("DEBUG [Parent]: New pipe FDs: read=%d, write=%d\n", 
		// 	pipe_fd[0], pipe_fd[1]);
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
	pid = fork();
	if (pid == -1)
		exit_perror("fork");
	if (pid == 0)
		setup_child_process(tokens, current, *prev_fd, pipe_fd);
	else
	{
		waitpid(pid, &status, 0);
	// Princy
		// if (WIFEXITED(status))
		// 	set_status(WEXITSTATUS(status));
		// else if(WIFSIGNALED(status))
		// 	set_status(WTERMSIG(status) + 128);
		// ft_putstr_fd("status:", 2);
		// ft_putnbr_fd(status, 2);
		// ft_putchar_fd('\n',2);
	}
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
// Princy
	// if (get_status() == 131)
	// 	ft_putstr_fd("Quit :Core dumped\n", 2);
}
