<p align="center" width="100">
    <img src=".Picture4rdme/minishell.png"/>
</p>


		(   si tu veux tu peux m expliquer le parsing avec lexing et la tokenisation ici brievement si ta le temps )

a faire aussi

   		finir parsing lexing token + new make file propre de nrico

       		finir commande a implementer + signal 

   		+ finir le reste harmonisation 

structure

 		  ├── from_pipex/
                   └──  execute_pipe.c
		   └── from_pipex.c
      		   └── pipex_path.c
	   
		            minishell/
            ├── built/       # → Tes builtins (echo, cd, exit, export, unset, env)
            │   ├── builtin.c
	    │   ├── echo.c
            │   ├── cd.c
            │   ├── exit.c
            │   ├── export.c
            │   ├── unset.c
            │   ├── env.c
            ├── parser/         # → Tokenisation, splitting, création AST
            |	|			 │   ├── lexer.c               \__ old_parser
            |	|			 │   ├── ast.c / ast_helper.c  /
            │   ├── parser.c				
	    │   ├── parsing.c
     	    │   ├── subtoken.c
	    │   ├── token_attribution.c
    	    │   ├── tokenizer.c
            ├── exec/           # → Exécution AST, pipeline, redirs
            │   ├── executor.c
            │   ├── pipe_utils.c # -> dans from_pipex
            │   ├── redirection.c
            ├── env/            # → Gestion env chaîné, export, unset, etc.
            │   ├── env_list.c
            │   ├── export.c
	    │   ├── unset.c
     	    │   ├── utils_env.c
            ├── signals/
            │   └── signals.c
            ├── handle_utils/          # → ft_split, ft_strjoin_3, ft_free_split etc.
            │   │   └── handler_cast_t_shell/
	    |	|	 └── handler-1.c
            |	|	 └── handler-2.c
	    │   └── util-0.c
	    │   └── util-1.c
     	    │   └── util-2.c
            │   └── util-3-free.c
            ├── main/
	    |	└── main_loop.c
            |	└── main.c
	    |	└── start_init.c
     	    |
            ├── Include
	    |	└── minishell.h
   	    |	└── ast.h
            |	└── env.h
	    |	└── parsing.h 	
            |	└── LIBFT
	    |	      └── libft.h
            ├── Makefile


			   parser/parser.c → parse l’input, remplit l’AST

            utils/utils.c → toutes les petites fonctions de split/join/free

            builtins/echo.c, builtins/cd.c → tes builtins

            env/env_list.c → init/free/print env chaîné

            env/export.c, env/unset.c

            redirection.c → setup_redirections, gestion des fd
     		    exec/executor.c → gère l’appel principal à l’exécuteur AST, builtins, etc.
 		           
