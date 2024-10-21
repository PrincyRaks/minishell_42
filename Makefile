CFLAGS= -Wall -Werror -Wextra

SRCS=	mandatory/main.c \
		mandatory/shell_loop.c

OBJS= $(SRCS:.c=.o)

INC= -I./includes

NAME= minishell

all: $(NAME)

%.o:%.c
	cc $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)

libft:
	make -C libft/

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean libft all re