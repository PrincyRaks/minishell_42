CFLAGS = -Wall -Werror -Wextra -g
CC= cc

SRCS = mandatory/main.c \
	   mandatory/handle_command/handle_command.c \
	   mandatory/handle_command/handle_command_utils.c \
	   mandatory/handle_command/handle_command_utils2.c \
       mandatory/shell_loop.c \
	   mandatory/executor.c \
	   mandatory/parsing/quotes_token.c \
	   mandatory/parsing/parse_utils.c \
	   mandatory/parsing/expand.c \
	   mandatory/parsing/handle_quotes.c \
	   mandatory/parsing/handle_flow.c \
	   mandatory/parsing/handle_specialchar.c \
	   mandatory/parsing/valid_in_loop.c \
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
	   mandatory/pipe/execute_pipe_utils.c \
	   mandatory/pipe/execute_single_command.c \
	   mandatory/pipe/utils.c \
	   mandatory/signals/signals.c \
	   mandatory/redirection/redirection_utils.c \
	   mandatory/redirection/redirections.c

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

vlg: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignore_readline.supp -s ./$(NAME)

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean libft all re vlg
