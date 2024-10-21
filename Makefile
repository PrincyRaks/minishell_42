CFLAGS = -Wall -Werror -Wextra

SRCS = mandatory/main.c \
       mandatory/shell_loop.c

OBJS = $(SRCS:.c=.o)

INC = -I./includes

NAME = minishell
LIBFT = libft/libft.a

all: libft $(NAME)

%.o: %.c
	cc $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)

libft:
	make -C libft/

fclean: clean
	 make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean libft all re
