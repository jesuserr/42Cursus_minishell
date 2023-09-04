# minishell

- Notas 04/09
- Se tiene que hacer que al salir con exit, salga con el numero de error indicado en el exit, y el codigo salida si no indica nada el usuarip tiene que ser el del ultimo comando ejecutado
- Error al introducir un comando del estilo ;s
- echo $ tiene que mostrar $
- Funciones no autorizadas
	sprintf
	history_length
	history_list
- builtin cd , error al borrar el directorio actual. 


Para compilar en linux  
LINK_FLAGS = -lreadline  

Para compilar en MacOS  
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include  
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline