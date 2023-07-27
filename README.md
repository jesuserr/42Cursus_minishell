# minishell

Para compilar en linux  
LINK_FLAGS = -lreadline  

Para compilar en MacOS  
COMP_FLAGS = -I/Users/$(USER)/.brew/opt/readline/include  
LINK_FLAGS = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

- Notas cescanue 27/07
- (solved - falta reducir una linea para que pase norminette) Bug en optain_path, al hacer un unset de la variable PATH, peta
- Posible bug en heredoc, dentr de heredoc haces ctrl-d da segmentacion fail (en cuanto controlemos las señales del sistema, veremos)
- Se tiene que alamcenar el estado del salida del ultimo comando ejecutado, de momento se borra, estan en minishell_executor_cmds.c funcion void	ft_executor_cmds_waitpid(t_list *lst)
- Unificar gestion de errores
- Comnandos built_ins --> Jesus
- Senales del sistema --> cescanue