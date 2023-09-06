# minishell

- Notas revisiones tras aplicar tester

- Echo builtin mejorado, hay que revisar que pasa que tras unas comillas se nos come el ultimo caracter. Ejemplo:
[echo "-n -n -n" -n hi] devuelve [-n -n -n -n h]

- Notas 04/09
- Error al introducir un comando del estilo ;s
- Funciones no autorizadas
	history_length
	history_list

Para compilar en linux  
LINK_FLAGS = -lreadline  

Para compilar en MacOS  
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include  
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline