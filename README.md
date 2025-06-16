<p align="center" width="100">
    <img src=".Picture4rdme/minishell.png"/>
</p>
            minishell/
            ├── builtins/       # → Tes builtins (echo, cd, exit, export, unset, env)
            │   ├── echo.c
            │   ├── cd.c
            │   ├── exit.c
            │   ├── export.c
            │   ├── unset.c
            │   ├── env.c
            ├── parser/         # → Tokenisation, splitting, création AST
            │   ├── lexer.c
            │   ├── parser.c
            │   ├── ast.c
            ├── exec/           # → Exécution AST, pipeline, redirs
            │   ├── executor.c
            │   ├── pipe_utils.c
            │   ├── redirection.c
            ├── env/            # → Gestion env chaîné, export, unset, etc.
            │   ├── env_list.c
            │   ├── export.c
            ├── signals/
            │   └── signals.c
            ├── utils/          # → ft_split, ft_strjoin_3, ft_free_split etc.
            │   └── utils.c
            ├── main.c
            ├── minishell.h
            ├── Makefile


a faire

            exec/executor.c → gère l’appel principal à l’exécuteur AST, builtins, etc.

            parser/parser.c → parse l’input, remplit l’AST

            utils/utils.c → toutes les petites fonctions de split/join/free

            builtins/echo.c, builtins/cd.c → tes builtins

            env/env_list.c → init/free/print env chaîné

            env/export.c, env/unset.c

            redirection.c → setup_redirections, gestion des fd
            
