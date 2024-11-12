CFLAGS = -Wall -Werror -Wextra

SRCS = mandatory/main.c \
       mandatory/shell_loop.c \
	   mandatory/executor.c \
	   mandatory/parsing/quotes_token.c \
	   mandatory/parsing/redemption.c \
	   mandatory/utils/free_memory.c \
	   mandatory/utils/counter.c \
	   mandatory/token/ft_args.c \
	   mandatory/token/init_token.c \
	   mandatory/token/token_utils.c \

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
