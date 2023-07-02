# minishell

Para compilar en linux
LINK_FLAGS = -lreadline 

Para compilar en MacOS
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline 