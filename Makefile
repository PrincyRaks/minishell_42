CFLAGS= -Wall -Werror -Wextra

SRCS=	./mandatory/main.c \

OBJS= $(SRCS:.c=.o)

NAME= minishell

all: $(NAME)

%.o:%.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re