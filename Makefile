CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = src/main.c \
	   src/handle_command/handle_command.c \
	   src/handle_command/getset_stdin_dup.c \
	   src/handle_command/getset_stdout_dup.c \
	   src/handle_command/handle_command_utils2.c \
       src/shell_loop.c \
	   src/executor.c \
	   src/parsing/handle_input_msh.c \
	   src/parsing/parse_utils.c \
	   src/parsing/expand.c \
	   src/parsing/handle_quotes.c \
	   src/parsing/handle_flow.c \
	   src/parsing/handle_specialchar.c \
	   src/parsing/valid_in_loop.c \
	   src/parsing/store_structs.c \
	   src/parsing/setter_utils.c \
	   src/utils/free_memory.c \
	   src/utils/counter.c \
	   src/utils/exception.c \
	   src/env/ft_getenv.c \
	   src/env/env_utils.c \
	   src/env/getset_env.c \
	   src/env/get_tabenv.c \
	   src/env/clean_env.c \
	   src/env/getset_export.c \
	   src/token/ft_args.c \
	   src/token/token_utils.c \
	   src/token/getset_first_token.c \
	   src/token/ft_cmd.c \
	   src/token/ft_token.c \
	   src/token/ft_flow.c \
	   src/builtins/ft_cd.c \
	   src/builtins/ft_pwd.c \
	   src/builtins/ft_exit.c \
	   src/builtins/ft_env.c \
	   src/builtins/ft_echo.c \
	   src/builtins/ft_export.c \
	   src/builtins/ft_unset.c \
	   src/builtins/execute_builtins.c \
	   src/utils/ft_utils.c \
	   src/pipe/execute_pipe.c \
	   src/pipe/execute_single_command.c \
	   src/pipe/utils.c \
	   src/pipe/getset_sigpipe.c \
	   src/pipe/check_command.c \
	   src/pipe/execute_command.c \
	   src/signals/signals.c \
	   src/signals/signals_utils.c \
	   src/signals/getset_status.c \
	   src/signals/handler_signal.c \
	   src/signals/getset_sigint.c \
	   src/redirection/heredoc_utils.c \
	   src/redirection/redirections.c \
	   src/redirection/handle_heredoc.c \
	   src/redirection/getset_num_file.c 

OBJS = $(SRCS:.c=.o)

INC = -I./includes
	
NAME = minishell

LIBFT = libft/libft.a

all: libft $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

libft:
	make -C libft/

leaks: all
	valgrind --suppressions=ignore_readline.supp --track-fds=yes --leak-check=full --show-leak-kinds=all  ./$(NAME)

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean libft all re leaks
