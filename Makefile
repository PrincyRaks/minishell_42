CFLAGS = -Wall -Werror -Wextra -g

SRCS = mandatory/main.c \
       mandatory/shell_loop.c \
	   mandatory/executor.c \
	   mandatory/parsing/array_tokens.c \
	   mandatory/parsing/quotes_token.c \
	   mandatory/parsing/parse_utils.c \
	   mandatory/parsing/expand.c \
	   mandatory/parsing/handle_quotes.c \
	   mandatory/utils/free_memory.c \
	   mandatory/utils/counter.c \
	   mandatory/env/ft_getenv.c \
	   mandatory/env/env_utils.c \
	   mandatory/env/getset_env.c \
	   mandatory/env/get_tabenv.c \
	   mandatory/env/getset_export.c \
	   mandatory/token/ft_args.c \
	   mandatory/token/token_utils.c \
	   mandatory/token/ft_cmd.c \
	   mandatory/token/ft_token.c \
	   mandatory/builtins/ft_cd.c \
	   mandatory/builtins/ft_pwd.c \
	   mandatory/builtins/ft_exit.c \
	   mandatory/builtins/ft_env.c \
	   mandatory/builtins/ft_echo.c \
	   mandatory/builtins/ft_export.c \
	   mandatory/builtins/ft_unset.c \
	   mandatory/utils/ft_utils.c \
	   mandatory/pipe/execute_pipeline.c \
	   mandatory/pipe/execute_single_command.c \

OBJS = $(SRCS:.c=.o)

INC = -I./includes
	
NAME = minishell
LIBFT = libft/libft.a

all: libft $(NAME)

%.o: %.c
	cc $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

libft:
	make -C libft/

clean:
	make clean -C libft/
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean libft all re
