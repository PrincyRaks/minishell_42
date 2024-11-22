CFLAGS = -Wall -Werror -Wextra

SRCS = mandatory/main.c \
       mandatory/shell_loop/shell_loop.c \
	   mandatory/shell_loop/loop_utils.c \
       mandatory/executor.c \
       mandatory/builtins/ft_cd.c \
       mandatory/builtins/ft_pwd.c \
       mandatory/builtins/ft_exit.c \
	   mandatory/redirections/parse_redirections_utils.c \
       mandatory/redirections/parse_redirections.c \
       mandatory/redirections/redirections.c 


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
