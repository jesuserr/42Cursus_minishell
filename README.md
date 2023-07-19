# minishell

Para compilar en linux  
LINK_FLAGS = -lreadline  

Para compilar en MacOS  
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include  
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

- Notas cescanue 19/07
- ENV, en cuando tengamos nuestra copia de variables de sistema, se tienen que modificar los siguientes ficheros/funciones
*	minishell_parser_env
*	minishell_exec
*	minishell_executor_check_cmds
*	minishell_executor_cms

- Notas cescanue 17/07

- Temas a comentar
- Uso de structura global, para temas especificos como env o msg de sistema
- (DONE) ft_split que tenga en cuenta las " y ' --> Jesus
- Unificar gestion de errores
- Crear copia de ENV y todo lo necesario para su gestion --> Jesus
- (SOLVED) Gestion de multiples FD y que hacer con los que son meramente transitorios, ejemplo: varios FDIN y solo se usa el ultimo
- (SOLVED) Orden de procesado de las redicciones, decidir en caso de multiples que hacer. Posible BUG de diseño (solucionable). 
- Ejecucion de comandos en paralelo, hacer el waitpid todos a la vez y cerrar de los FD en funcion de que vayan terminando los procesos. -->cescanue
- Comnandos built_ins --> Jesus
- Senales del sistema --> cescanue