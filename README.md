# minishell

Para compilar en linux  
LINK_FLAGS = -lreadline  

Para compilar en MacOS  
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include  
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

- Notas cescanue 17/07

- Temas a comentar
- Uso de structura global, para temas especificos como env o msg de sistema
- Unificar gestion de errores
- Crear copia de ENV y todo lo necesario para su gestion
- Gestion de multiples FD y que hacer con los que son meramente transitorios, ejemplo: varios FDIN y solo se usa el ultimo
- Orden de procesado de las redicciones, decidir en caso de multiples que hacer. Posible BUG de diseño (solucionable). 
- Ejecucion de comandos en paralelo, hacer el waitpid todos a la vez y cerrar de los FD en funcion de que vayan terminando los procesos. 
- Comnandos built_ins, como tratar las redirecciones y pipes.  

- Notas sobre push J.S. 12/07  

- El ft_printf ahora imprime por el STDERR para poder imprimir mensajes de error  
- Para imprimir por STDOUT usamos el printf normal  
- Ahora se diferencia entre fallo por fichero no encontrado o no ejecutable (no completado del todo)  
- Minishell_exec rehecho casi del todo...  
- He convertido la struct actual en una struct perteneciente al minishell_exec ya que he visto que no la usas para nada en el parser    
