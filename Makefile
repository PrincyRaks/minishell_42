CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = mandatory/main.c \
	   mandatory/handle_command/handle_command.c \
	   mandatory/handle_command/getset_stdin_dup.c \
	   mandatory/handle_command/getset_stdout_dup.c \
	   mandatory/handle_command/handle_command_utils2.c \
       mandatory/shell_loop.c \
	   mandatory/executor.c \
	   mandatory/parsing/handle_input_msh.c \
	   mandatory/parsing/parse_utils.c \
	   mandatory/parsing/expand.c \
	   mandatory/parsing/handle_quotes.c \
	   mandatory/parsing/handle_flow.c \
	   mandatory/parsing/handle_specialchar.c \
	   mandatory/parsing/valid_in_loop.c \
	   mandatory/parsing/store_structs.c \
	   mandatory/parsing/setter_utils.c \
	   mandatory/utils/free_memory.c \
	   mandatory/utils/counter.c \
	   mandatory/utils/exception.c \
	   mandatory/env/ft_getenv.c \
	   mandatory/env/env_utils.c \
	   mandatory/env/getset_env.c \
	   mandatory/env/get_tabenv.c \
	   mandatory/env/clean_env.c \
	   mandatory/env/getset_export.c \
	   mandatory/token/ft_args.c \
	   mandatory/token/token_utils.c \
	   mandatory/token/getset_first_token.c \
	   mandatory/token/ft_cmd.c \
	   mandatory/token/ft_token.c \
	   mandatory/token/ft_flow.c \
	   mandatory/builtins/ft_cd.c \
	   mandatory/builtins/ft_pwd.c \
	   mandatory/builtins/ft_exit.c \
	   mandatory/builtins/ft_env.c \
	   mandatory/builtins/ft_echo.c \
	   mandatory/builtins/ft_export.c \
	   mandatory/builtins/ft_unset.c \
	   mandatory/builtins/execute_builtins.c \
	   mandatory/utils/ft_utils.c \
	   mandatory/pipe/execute_pipe.c \
	   mandatory/pipe/execute_single_command.c \
	   mandatory/pipe/utils.c \
	   mandatory/pipe/getset_sigpipe.c \
	   mandatory/pipe/check_command.c \
	   mandatory/pipe/execute_command.c \
	   mandatory/signals/signals.c \
	   mandatory/signals/signals_utils.c \
	   mandatory/signals/getset_status.c \
	   mandatory/signals/handler_signal.c \
	   mandatory/signals/getset_sigint.c \
	   mandatory/redirection/heredoc_utils.c \
	   mandatory/redirection/redirections.c \
	   mandatory/redirection/handle_heredoc.c \
	   mandatory/redirection/getset_num_file.c 

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
	valgrind --vgdb=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp -s ./$(NAME)

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean libft all re leaks
