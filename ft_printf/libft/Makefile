NAME		= libft.a
INCLUDE		= include
SRC_DIR		= srcs/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f
AR			= ar rcs
SRC_FILES	= ft_memset \
			  ft_bzero \
			  ft_memcpy \
			  ft_memmove \
			  ft_memchr \
			  ft_strlen \
			  ft_strchr \
			  ft_strrchr \
			  ft_strncmp \
			  ft_isalpha \
			  ft_isdigit \
			  ft_isalnum \
			  ft_isascii \
			  ft_isprint \
			  ft_toupper \
			  ft_tolower \
			  ft_memcmp \
			  ft_strlcpy \
			  ft_strlcat \
			  ft_strnstr \
			  ft_atoi \
			  ft_calloc \
			  ft_strdup \
			  ft_substr \
			  ft_strjoin \
			  ft_strtrim \
			  ft_split \
			  ft_itoa \
			  ft_strmapi \
			  ft_striteri \
			  ft_putchar_fd \
			  ft_putstr_fd \
			  ft_putendl_fd \
			  ft_putnbr_fd \
			  ft_lstnew \
			  ft_lstadd_front \
			  ft_lstsize \
			  ft_lstlast \
			  ft_lstadd_back \
			  ft_lstdelone \
			  ft_lstclear \
			  ft_lstiter \
			  ft_lstmap \
			  ft_lstfind \
			  
			  

HEADER		=	includes/libft.h
		
SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(AR) $(NAME) $(OBJ)
			@ranlib	$(NAME)
			@echo "LIBFT compiled!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)
		
clean:
			@$(RM) -rf $(OBJ_DIR)

fclean:		clean
			@$(RM) -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re 