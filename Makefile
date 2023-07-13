NAME		= minishell
NAMEB		= minishell_bonus
INCLUDE		= includes
INCLUDEB	= includes_bonus
SRC_DIR		= srcs/
SRC_DIRB	= srcs/bonus/
OBJ_DIR		= obj/
CC			= cc
CFLAGSO		= -Werror -Wall -Wextra -I/Users/$(USER)/.brew/opt/readline/include -I
CFLAGSE		= -Werror -Wall -Wextra -L/Users/$(USER)/.brew/opt/readline/lib -lreadline -Lft_printf -l$(LIB) -I
RM			= rm -f
FT_PRINTF	= ft_printf
LIBFT		= ft_printf/libft
LIB			= ftprintf

SRC_FILES	= minishell \
			  minishell_error \
			  minishell_parser \
			  minishell_parser_error \
			  minishell_parser_blocks \
			  minishell_parser_to_struct \
			  minishell_parser_to_struck_pattern \
			  minishell_parser_to_struct_cmd \
			  minishell_parser_to_struck_utils \
			  minishell_parser_to_struct_type \
			  minishell_parser_env \
			  minishell_exec \
			  minishell_utils
			  
SRC_FILESB	= 
		  
HEADER		=	includes/minishell.h \

HEADERB		=	

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJB 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILESB)))

OBJF		=	.cache_exists

all:		make_libs $(NAME)

make_libs:
			@make -C $(FT_PRINTF)

$(NAME):	$(OBJ) ft_printf/libftprintf.a
			@$(CC) $(CFLAGSE) $(INCLUDE) $(OBJ) -o $(NAME)
			@echo "Minishell compiled!"
			
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJF)
			@$(CC) $(CFLAGSO) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIRB)%.c $(HEADERB) | $(OBJF)
			@$(CC) $(CFLAGSO) $(INCLUDEB) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

bonus:		make_libs $(NAMEB)

$(NAMEB):	$(OBJB)
			@$(CC) $(CFLAGS) $(INCLUDEB) $(OBJB) -o $(NAMEB)
			@echo "Minishell_bonus compiled!"

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(FT_PRINTF)
			@make clean -C $(LIBFT)
			
fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(NAMEB)
			@$(RM) -f $(LIBFT)/libft.a
			@$(RM) -f $(FT_PRINTF)/libftprintf.a	
			
re:			fclean all

.PHONY:		all clean fclean re