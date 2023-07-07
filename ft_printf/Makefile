NAME		= libftprintf.a
INCLUDE		= includes
LIBFT		= libft
SRC_DIR		= srcs/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
CFLAGSTEST	= -I
RM			= rm -f
AR			= ar rcs
TEST		= test.c
LIBTEST		= ftprintf
SRC_FILES	=	ft_printf \
				ft_printf_utils \
				ft_printf_parse \
				ft_printf_getvalues \
				ft_printf_getvalues2 \
				ft_printf_format \
				ft_printf_format2 \
				ft_printf_numbers \

HEADER		=	includes/ft_printf.h

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

all:		make_libs $(NAME)

make_libs:
			@make -C $(LIBFT)

$(NAME):	$(OBJ) libft/libft.a
			@cp libft/libft.a .
			@mv libft.a $(NAME)
			@$(AR) $(NAME) $(OBJ)
			@ranlib	$(NAME)
			@echo "FT_PRINTF compiled!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

bonus:		all

test:		all
			$(CC) $(TEST) -L. -l$(LIBTEST) $(CFLAGSTEST) $(INCLUDE)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIBFT)

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(LIBFT)/libft.a
			@$(RM) -f ./a.out

re:			fclean all

.PHONY:		all clean fclean re test