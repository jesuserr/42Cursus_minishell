# minishell

Para compilar en linux  
LINK_FLAGS = -lreadline  

Para compilar en MacOS  
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include  
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

- Notas sobre push J.S. 12/07  

- El ft_printf ahora imprime por el STDERR para poder imprimir mensajes de error  
- Para imprimir por STDOUT usamos el printf normal  
- Ahora se diferencia entre fallo por fichero no encontrado o no ejecutable (no completado del todo)  
- Minishell_exec rehecho casi del todo...  
- He convertido la struct actual en una struct perteneciente al minishell_exec ya que he visto que no la usas para nada en el parser    





