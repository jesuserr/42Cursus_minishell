# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 10:58:03 by jesuserr          #+#    #+#              #
#    Updated: 2023/07/02 10:58:03 by jesuserr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft/

NAME = minishell
SRCS = main.c utils.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

INCLUDE = -I./ -I./libft/includes/
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline 

NORM = ${SRCS} minishell.h
GREEN = "\033[0;92m"
RED = "\033[0;91m"
BLUE = "\033[0;94m"
NC = "\033[37m"

all: makelibft $(NAME)

makelibft:
	@make --no-print-directory -C $(LIBFT_DIR)	
	@echo ${GREEN}"Libft Compiled!\n"${NC};

%.o: %.c
	$(CC) $(CFLAGS) -MMD $(INCLUDE) ${COMP_FLAGS} -c $< -o $@
	
$(NAME): $(OBJS) $(LIBFT_DIR)libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)libft.a ${LINK_FLAGS} -o $@
	@echo ${GREEN}"minishell Compiled!\n"${NC};
-include $(DEPS)

clean:
	@make clean --no-print-directory -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(DEPS)
		
fclean:
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(DEPS)
	$(RM) $(NAME)

norm:
	@echo ${BLUE}"\nChecking Norminette..."${NC}
	@if norminette $(NORM); then echo ${GREEN}"Norminette OK!\n"${NC}; \
	else echo ${RED}"Norminette KO!\n"${NC}; \
	fi

re: fclean all

.PHONY: all clean fclean re makelibft norm
