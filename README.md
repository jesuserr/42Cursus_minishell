Mandatory part + Bonus -> 101%

Minishell - As beautiful as a shell

Summary: This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.

For detailed information, refer to the subject of this project

In order to have a successfull compilation the Readline library must be present. For this project the library was installed using Brew.  
In any other case it may be needed to modify the following Makefile lines:  

CFLAGSO		= -Werror -Wall -Wextra -I/opt/homebrew/opt/readline/include -I  
CFLAGSE		= -Werror -Wall -Wextra -L/opt/homebrew/opt/readline/lib -lreadline -Lft_printf -l$(LIB) -I
