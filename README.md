      ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓         ⠀⢀⣀⠀⠀⠀⠀⠀⢠⠖⠁⠀⠀⠀⠀⠀⠀⠢⣥⣢⠀⠀⠀⠀⠀⣠⣤⠀
     ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒         ⢀⣟⣿⣦⠀⠀⠀⣰⡿⠿⠷⠶⣄⠀⠀⢠⠾⠟⠛⠛⢷⡀⠀⢀⡼⣿⣇⡇
     ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░         ⠈⠛⠛⠿⢕⡂⢴⠁⠀⠀⠀⢀⠈⠆⠠⣮⣴⢤⡀⣀⣸⣗⣶⡧⠒⠉⠉⠁
     ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░         ⠀⠀⠀⠀⠀⢹⠀⠀⠴⣺⣿⣿⠇⠀⠀⠛⡿⣽⣿⣽⠿⠛⢻⠀⠀⠀⠀⠀
     ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒     ⠀⠀⠀⠀⠀⡌⠀⠀⠈⠉⢩⠀⠀⠀⠀⠀⣸⣒⣄⠀⠀⠀⠀⠇⠀⠀⠀⠀
     ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░     ⠀⠀⠀⠀⠀⡇⠀⢀⡴⠖⠉⠛⠓⠲⠶⠾⠿⠿⠿⢏⡳⡀⠄⣾⠀⠀⠀⠀
      ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░    ⠀⠀⠀⠀⠀⠃⠀⠞⠀⣀⣀⣀⣀⣀⣀⣀⣤⣤⣶⣿⣇⢧⠀⣿⠀⠀⠀⠀
      ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░       ⠀⠀⠀⠀⠀⡄⠀⠀⠀⠈⠫⢽⣽⣉⣹⣁⣧⣿⠟⣱⣿⣾⢀⣿⠀⠀⠀⠀
           ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░      ⠀⠀⠀⠀⠀⢃⠀⠀⠀⠀⠀⠀⠉⠙⠩⠤⠭⣶⣋⡟⢸⢁⣿⠏⠀⠀⠀⠀
                                                                                ⠀⠀⠀⠀⠀⠀⠱⡀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠝⡇⣘⡾⠋⠀⠀⠀⠀⠀
          )))         ╔╗╔┌─┐┌─┐   ┬   ╔═╗┌┐┌┬─┐┬┌─┐┌─┐          (((             ⠀⠀⠀⠀⠀⠀⠀⠈⠢⣀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣷⠋⠀⠀⠀⠀⠀⠀⠀
         (o o)        ║║║│ │├┤   ┌┼─  ║╣ │││├┬┘││  │ │         (o o)            ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠠⠤⠤⠤⠤⠾⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀
        --(_)--       ╝╚╝└─┘└─┘  └┘   ╚═╝┘└┘┴└─┴└─┘└─┘        --(_)--           








		/usr/bin/ld: obj/parser/launch.o: in function `launch_process':
launch.c:(.text+0x68a): undefined reference to `execute_cmd'
/usr/bin/ld: obj/parser/lexer.o: in function `count_args_cmd':
lexer.c:(.text+0x77c): undefined reference to `print_dic'
/usr/bin/ld: obj/parser/path.o: in function `expand_variable':
path.c:(.text+0x4d4): undefined reference to `get_value_env'
/usr/bin/ld: obj/parser/path.o: in function `expand_str':
path.c:(.text+0x5ff): undefined reference to `get_value_env'
/usr/bin/ld: obj/parser/tool_lexer.o: in function `count_tokens':
tool_lexer.c:(.text+0x2f7): undefined reference to `ft_free'
/usr/bin/ld: tool_lexer.c:(.text+0x31a): undefined reference to `ft_free'
clang: error: linker command failed with exit code 1 (use -v to see invocation)
make: *** [Makefile:68: minishell] Error 1


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


-A action
                      The action may be one of the following to generate a list of possible completions:
                      alias   Alias names.  May also be specified as -a.
                      arrayvar
                              Array variable names.
                      binding Readline key binding names.
                      builtin Names of shell builtin commands.  May also be specified as -b.
                      command Command names.  May also be specified as -c.
                      directory
                              Directory names.  May also be specified as -d.
                      disabled
                              Names of disabled shell builtins.
                      enabled Names of enabled shell builtins.
                      export  Names of exported shell variables.  May also be specified as -e.
                      file    File names.  May also be specified as -f.
                      function
                              Names of shell functions.
                      group   Group names.  May also be specified as -g.
                      helptopic
                              Help topics as accepted by the help builtin.
                      hostname
                              Hostnames, as taken from the file specified by the HOSTFILE shell variable.
                      job     Job names, if job control is active.  May also be specified as -j.
                      keyword Shell reserved words.  May also be specified as -k.
                      running Names of running jobs, if job control is active.
                      service Service names.  May also be specified as -s.
                      setopt  Valid arguments for the -o option to the set builtin.
                      shopt   Shell option names as accepted by the shopt builtin.
                      signal  Signal names.
                      stopped Names of stopped jobs, if job control is active.
                      user    User names.  May also be specified as -u.
                      variable
                              Names of all shell variables.  May also be specified as -v.
              -C command
                      command is executed in a subshell environment, and its output is used as the possible completions.  Arguments are passed as with the -F option.
              -F function
                      The shell function function is executed in the current shell environment.  When the function is executed, the first argument ($1) is the name of
                      the command whose arguments are being completed, the second argument ($2) is the word being completed, and the third argument ($3) is  the  word
                      preceding  the word being completed on the current command line.  When it finishes, the possible completions are retrieved from the value of the
                      COMPREPLY array variable.

          echo [-neE] [arg ...]
              Output the args, separated by spaces, followed by a newline.  The return status is 0 unless a write error occurs.  If -n is specified, the trailing new‐
              line is suppressed.  If the -e option is given, interpretation of the following backslash-escaped characters is enabled.  The -E option disables the in‐
              terpretation of these escape characters, even on systems where they are interpreted by default.  The xpg_echo shell option may be  used  to  dynamically
              determine  whether  or not echo expands these escape characters by default.  echo does not interpret -- to mean the end of options.  echo interprets the
              following escape sequences:
              \a     alert (bell)
              \b     backspace
              \c     suppress further output
              \e
              \E     an escape character
              \f     form feed
              \n     new line
              \r     carriage return
              \t     horizontal tab
              \v     vertical tab
              \\     backslash
              \0nnn  the eight-bit character whose value is the octal value nnn (zero to three octal digits)
              \xHH   the eight-bit character whose value is the hexadecimal value HH (one or two hex digits)
              \uHHHH the Unicode (ISO/IEC 10646) character whose value is the hexadecimal value HHHH (one to four hex digits)
              \UHHHHHHHH
                     the Unicode (ISO/IEC 10646) character whose value is the hexadecimal value HHHHHHHH (one to eight hex digits)
    
           exit [n]
              Cause  the  shell to exit with a status of n.  If n is omitted, the exit status is that of the last command executed.  A trap on EXIT is executed before
              the shell terminates.

          export [-fn] [name[=word]] ...
          export -p
              The supplied names are marked for automatic export to the environment of subsequently executed commands.  If the -f option is given, the names refer  to
              functions.   If no names are given, or if the -p option is supplied, a list of names of all exported variables is printed.  The -n option causes the ex‐
              port property to be removed from each name.  If a variable name is followed by =word, the value of the variable is set to word.  export returns an  exit
              status  of  0  unless an invalid option is encountered, one of the names is not a valid shell variable name, or -f is supplied with a name that is not a
              function.
        pwd [-LP]
              Print the absolute pathname of the current working directory.  The pathname printed contains no symbolic links if the -P option is supplied  or  the  -o
              physical option to the set builtin command is enabled.  If the -L option is used, the pathname printed may contain symbolic links.  The return status is
              0 unless an error occurs while reading the name of the current directory or an invalid option is supplied.
        
        unset [-fv] [-n] [name ...]
              For each name, remove the corresponding variable or function.  If the -v option is given, each name refers to a shell variable, and that variable is re‐
              moved.  Read-only variables may not be unset.  If -f is specified, each name refers to a shell function, and the function definition is removed.  If the
              -n option is supplied, and name is a variable with the nameref attribute, name will be unset rather than the variable it references.  -n has  no  effect
              if  the  -f  option is supplied.  If no options are supplied, each name refers to a variable; if there is no variable by that name, a function with that
              name, if any, is unset.  Each unset variable or function is removed from the environment  passed  to  subsequent  commands.   If  any  of  BASH_ALIASES,
              BASH_ARGV0,  BASH_CMDS, BASH_COMMAND, BASH_SUBSHELL, BASHPID, COMP_WORDBREAKS, DIRSTACK, EPOCHREALTIME, EPOCHSECONDS, FUNCNAME, GROUPS, HISTCMD, LINENO,
              RANDOM, SECONDS, or SRANDOM are unset, they lose their special properties, even if they are subsequently reset.  The exit status is true unless  a  name
              is readonly or may not be unset.

         wait [-fn] [-p varname] [id ...]
              Wait  for  each  specified child process and return its termination status.  Each id may be a process ID or a job specification; if a job spec is given,
              all processes in that job's pipeline are waited for.  If id is not given, wait waits for all running background jobs and the last-executed process  sub‐
              stitution,  if its process id is the same as $!, and the return status is zero.  If the -n option is supplied, wait waits for a single job from the list
              of ids or, if no ids are supplied, any job, to complete and returns its exit status.  If none of the supplied arguments is a child of the shell,  or  if
              no  arguments are supplied and the shell has no unwaited-for children, the exit status is 127.  If the -p option is supplied, the process or job identi‐
              fier of the job for which the exit status is returned is assigned to the variable varname named by the option argument.  The variable will be unset ini‐
              tially, before any assignment.  This is useful only when the -n option is supplied.  Supplying the -f option, when job control is enabled,  forces  wait
              to  wait  for  id to terminate before returning its status, instead of returning when it changes status.  If id specifies a non-existent process or job,
              the return status is 127.  If wait is interrupted by a signal, the return status will be greater than 128, as described under SIGNALS in bash(1).   Oth‐
              erwise, the return status is the exit status of the last process or job waited for.




<p align="center" width="100">
    <img src=".Picture4rdme/minishell.png"/>
</p>
