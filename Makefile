CFLAGS= -Wall -Werror -Wextra

SRCS=	./mandatory/main.c \

OBJS= $(SRCS:.c=.o)

INC= -I./includes

NAME= minishell

all: $(NAME)

%.o:%.c
	gcc $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

libft:
	make -C libft/

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean libft all re