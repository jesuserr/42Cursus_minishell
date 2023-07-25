# minishell

Para compilar en linux  
LINK_FLAGS = -lreadline  

Para compilar en MacOS  
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include  
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

- Notas cescanue 25/07
- Posible bug en heredoc, dentr de heredoc haces ctrl-d da segmentacion fail (en cuanto controlemos las señales del sistema, veremos)
- Notas cescanue 24/07
- (SOLVED) bug, revisar combinacion de redirecciones y pipes, ejemplo:  cat < README.md | wc -l
- (SOLVED) bug, muestra que no se puede ejecutar comando, si el comando esta vacio.  
- Falta el control de errores en minishell_exec_pipes en los dup2
- (SOLVED) Bug, si se pone una coma entre comillas, lo interpreta como otro bloque, revisar.
- Se tiene que alamcenar el estado del salida del ultimo comando ejecutado, de momento se borra, estan en minishell_executor_cmds.c funcion void	ft_executor_cmds_waitpid(t_list *lst)
- Notas cescanue 19/07
- ENV, en cuando tengamos nuestra copia de variables de sistema, se tienen que modificar los siguientes ficheros/funciones
*	minishell_parser_env
*	minishell_exec
*	minishell_executor_check_cmds
*	minishell_executor_cmd
- (No hace falta el bash se comporta de la misma forma) Tenemos que buscar la forma de controlar de imprimier \n en caso que el ultimo programa no lo haga, se pude hacer duplicado del fd del STDOUT

- Notas cescanue 17/07

- Temas a comentar
- Uso de structura global, para temas especificos como env o msg de sistema
- (DONE) ft_split que tenga en cuenta las " y ' --> Jesus
- Unificar gestion de errores
- (DONE) Crear copia de ENV y todo lo necesario para su gestion --> Jesus
- (SOLVED) Gestion de multiples FD y que hacer con los que son meramente transitorios, ejemplo: varios FDIN y solo se usa el ultimo
- (SOLVED) Orden de procesado de las redicciones, decidir en caso de multiples que hacer. Posible BUG de diseño (solucionable). 
- (DONE) Ejecucion de comandos en paralelo, hacer el waitpid todos a la vez y cerrar de los FD en funcion de que vayan terminando los procesos. -->cescanue
- Comnandos built_ins --> Jesus
- Senales del sistema --> cescanue