
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
            
