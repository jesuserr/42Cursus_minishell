NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c \
is/ft_isalnum.c is/ft_isalpha.c is/ft_isascii.c is/ft_isdigit.c is/ft_isprint.c \
lst/ft_lstnew.c lst/ft_lstadd_front.c lst/ft_lstsize.c \
lst/ft_lstlast.c lst/ft_lstadd_back.c lst/ft_lstdelone.c \
lst/ft_lstclear.c lst/ft_lstiter.c lst/ft_lstmap.c \
mem/ft_memchr.c mem/ft_memcmp.c mem/ft_memcpy.c mem/ft_memmove.c mem/ft_memset.c \
mem/ft_calloc.c mem/ft_bzero.c \
printf/ft_printf.c printf/ft_put_nums.c printf/ft_put_text.c \
put/ft_putchar_fd.c put/ft_putstr_fd.c put/ft_putendl_fd.c put/ft_putnbr_fd.c \
str/ft_strchr.c str/ft_strdup.c str/ft_striteri.c str/ft_strjoin.c \
str/ft_strlcat.c str/ft_strlcpy.c str/ft_strlen.c str/ft_strmapi.c \
str/ft_strncmp.c str/ft_strnstr.c str/ft_strrchr.c str/ft_strtrim.c \
str/ft_substr.c str/ft_split.c str/ft_strspn.c str/ft_strcspn.c \
str/ft_strstr.c \
to/ft_tolower.c to/ft_toupper.c to/ft_atoi.c to/ft_itoa.c \

OBJS = $(SRCS:.c=.o)
INCLUDE = -I ./includes
RM = rm -f
DEPS = $(SRCS:.c=.d)

%.o: %.c
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)
-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re