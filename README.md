# minishell

Para compilar en linux  
LINK_FLAGS = -lreadline  

Para compilar en MacOS  
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include  
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

- Notas cescanue 28/07
- Estadod de salida
- - Se guarda el estado de salida de los procesos, pero se hace de forma secuencial, por lo que no es el del ultimo, revisar. 
- - No se controla que si trata de ejecutar algo que no existe, el valor de las status tiene que ser 127
- Posible bug en heredoc, dentr de heredoc haces ctrl-d da segmentacion fail (en cuanto controlemos las señales del sistema, veremos)
- Se tiene que alamcenar el estado del salida del ultimo comando ejecutado, de momento se borra, estan en minishell_executor_cmds.c funcion void	ft_executor_cmds_waitpid(t_list *lst)
- Unificar gestion de errores
- Comnandos built_ins --> Jesus
- Senales del sistema --> cescanue