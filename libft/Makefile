CFLAGS= -Wall -Wextra -Werror
SRC= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isspace.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
SRC_bonus= ft_lstadd_front_bonus.c  ft_lstlast_bonus.c  ft_lstnew_bonus.c	ft_lstsize_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJS= $(SRC:.c=.o)
OBJS_bonus = $(SRC_bonus:.c=.o)
NAME= libft.a

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $(SRC) $(SRC_bonus)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(OBJS_bonus)
	ar rcs $(NAME) $(OBJS) $(OBJS_bonus)

clean:
	rm -f $(OBJS) $(OBJS_bonus)

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY: clean fclean re bonus all
