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






        Anatomie complète de MINISHELL
        1. Structure centrale

        Le programme repose sur la structure t_shell, véritable « noyau » de l’exécution : 
        elle enregistre l’environnement, les arguments bruts, le tableau de tokens, la liste chaînée de commandes, 
        les redirections, un tableau de PIDs, les copies de stdin/stdout, ainsi que l’état du terminal.
        Une variable globale g_exit_status, déclarée volatile sig_atomic_t, sert de canal de communication entre la 
        boucle principale et les gestionnaires de signaux pour reporter la cause de la dernière terminaison (code de retour ou signal).
        2. Initialisation (SRC/init)
        start_shell efface la structure, configure le terminal (term_init), installe les handlers de signaux (init_signals) et transforme 
        envp en liste chaînée (init_env). Les redirections et tableaux         de commandes sont initialisés à des états neutres.

            term_init récupère les attributs du terminal, désactive l’affichage de ^C et applique les réglages adaptés au mode canonique.

            init_signals installe handle_sigint et handle_sigquit, tandis que parent_signals/child_signals rétablissent l’ignorance ou le 
            comportement par défaut lors des forks.

            t_arr et t_dic (sous-dossier t_arr/) implémentent des tableaux dynamiques utilisés pour indexer les builtins (bcmd) et les opérateurs (oper).

        3. Boucle principale (SRC/main)

            main vérifie l’absence d’arguments, affiche une bannière puis lance start_shell et looping.

            looping lit chaque ligne via read_user_input, recopie g_exit_status dans shell->exit_status, et confie la chaîne à process_input.

            process_input découpe le traitement en quatre étapes :

                early_stage – gestion des quotes multi‑lignes, historique, détection de exit

                expand_stage – expansion de $? et autres variables

                parse_stage – tokenisation, association des redirections, construction de la liste de commandes

                run_stage – lancement des commandes puis nettoyage des allocations.

        4. Lexing & Parsing (SRC/fck_split, SRC/parser)

            custom_split (fichiers split_count-arg.c/split_extract-arg.c) segmente la ligne en respectant les quotes et les opérateurs.

            attribute_token_type classe chaque segment en TOKEN_CMD, TOKEN_BCMD, TOKEN_PIPE, etc.

            assign_redirs analyse la liste d’arguments, détache les opérateurs de redirection et relie le fichier cible à la commande courante.

            build_cmd_list convertit le tableau de tokens en liste chaînée de commandes prêtes à l’exécution, en sauvegardant pour chacune les 
            éventuelles redirections et le compte d’arguments.

        5. Gestion de l’environnement (SRC/env)

            init_env convertit le tableau envp en liste de nœuds t_env{key,value}, alloués dynamiquement ; chaque nœud est chaîné dans shell->env.

            list_to_envp recompresse la liste en tableau char ** avant un execve, ne conservant que les variables exportables (valeur non NULL).

            set_env_value/unset_env permettent aux builtins export et unset de modifier la liste.

        6. Builtins (SRC/built)

            is_builtin identifie les commandes internes (cd, echo, pwd, export, unset, env, exit).

            get_builtin_handler renvoie le pointeur de fonction dans bcmd, stocké comme dictionnaire dynamique.

            builtin_cd contrôle le nombre d’arguments, choisit la destination (HOME, OLDPWD ou argument explicite), réalise le chdir 
            puis met à jour PWD et OLDPWD dans l’environnement.

            builtin_echo reconnaît les options -n, traite les variables (via replace_variables.c) et imprime les arguments 
            en tenant compte des quotes et des échappements.

            builtin_exit valide l’argument numérique, gère l’erreur « too many arguments » et quitte le shell en libérant toutes les ressources.

            export et unset manipulent la liste d’environnement ; env affiche les variables ; pwd utilise getcwd pour afficher le répertoire courant.

        7. Expansion avancée (SRC/expand, SRC/parser/expand_p)

            expand_input remplace d’abord $? par shell->exit_status grâce à replace_exit.c, tout en respectant les quotes : 
            le parcours tient compte des contextes in_sq/in_dq pour éviter les expansions interdites.

            Dans parser/expand_p/expand_container.c, chaque argument est découpé en sous‑tokens (texte, variable), 
            résolu avec l’environnement puis recomposé ; les quotes sont retirées par remove_quotes.

        8. Exécution (SRC/parser/launch, SRC/exec)

            Préparatifs
            launch_process restaure le terminal, prépare les heredocs et, si la ligne se réduit à un seul builtin, 
            l’exécute directement dans le processus courant (run_single_builtin_if_alone).

            Fork/pipe
            Pour chaque commande d’un pipeline :

                check_pipe ouvre un pipe si nécessaire ;

                try_fork_and_run effectue le fork, configure les signaux (parent_signals/child_signals)
                puis confie au fils child_exec l’application des redirections et l’exécution de la commande.

                Le parent referme les extrémités inutilisées et enregistre le PID.

            Exécution réelle

                prepare_or_run_builtin développe les arguments (expand_cmd) ; si le premier est un builtin, il est exécuté immédiatement ; 
                sinon, le tableau d’arguments est renvoyé au lanceur externe.

                execute_cmd cherche le binaire (find_command_path), construit envp (list_to_envp) et invoque execve. 
                En cas d’échec (ENOENT, EACCES, etc.) un message est émis et le processus fils quitte avec le code approprié.

            Attente et statut
            wait_all_update_status récupère non‑bloquant les fils déjà terminés, puis attend les autres. 
            Pour le dernier PID, g_exit_status prend soit le code de retour (WIFEXITED), soit 128 + signal (WIFSIGNALED) ; le shell imprime ^C ou Quit (core dumped) si nécessaire.

        9. Redirections & Heredocs (SRC/redir)

            assign_redirs lors du parsing associe chaque opérateur >, >>, <, << au bon token‑commande.

            handle_redirect_in/out/append ouvre les fichiers et met à jour shell->fd_in/fd_out; la fonction vérifie les erreurs d’ouverture et affiche des diagnostics standardisés.

            prepare_heredoc crée des fichiers temporaires, lit jusqu’au délimiteur, applique l’expansion sauf si le délimiteur est quote, et remplace fd_in par ce fichier.

            apply_redirs_in_child (appelée depuis child_exec) duplique fd_in/fd_out vers STDIN_FILENO et STDOUT_FILENO pour rediriger les flux.

        10. Utilitaires (SRC/handle_utils, SRC/utils)

            update_quotes maintient les drapeaux in_sq/in_dq pour tout le parsing afin d’ignorer les $ ou | protégés par des quotes.

            Les sous-modules util-*-free.c libèrent tokens, commandes, tableaux et heredocs après chaque ligne (cleanup_shell_iter) ou à la fermeture (free_minishell).

            handler-1.c/handler-2.c centralisent les erreurs critiques (allocation, redirection, etc.) pour éviter les fuites de mémoire.

        11. Déroulement complet du programme

        main
        │
        ├─ start_shell : init_env, term_init, init_signals, init_all_t_arr
        │
        └─ looping
           ├─ read_user_input → readline
           └─ process_input
               ├─ early_stage       (read_more, add_history, must_exit)
               ├─ expand_stage      (expand_input)
               ├─ parse_stage       (custom_split → tokens → assign_redirs → build_cmd_list)
               └─ run_stage
                   └─ launch_process
                       ├─ prepare_heredocs
                       ├─ run_single_builtin_if_alone ? (sans fork)
                       └─ pour chaque commande :
                           ├─ pipe / fork
                           ├─ child_exec (dup2, apply_redirs_in_child, execute_cmd ou builtin)
                           └─ parent_after_fork (ferme fd, enregistre pid)
                       └─ wait_all_update_status

        12. Exécution d’une commande avec pipes & redirections

        Exemple : cat < in.txt | grep foo | wc -l >> out.txt

        [Parent]
          pipe(p1) ── fork → child1
          pipe(p2) ── fork → child2
                       └── fork → child3
          ferme fds inutiles, attend tous les enfants
          └─ wait_all_update_status → g_exit_status = code final

        [child1] cat
          open("in.txt", RDONLY) → dup2(fd, STDIN)
          dup2(p1[1], STDOUT)
          close(p1[0], p1[1], ...)
          execve("cat")

        [child2] grep foo
          dup2(p1[0], STDIN)
          dup2(p2[1], STDOUT)
          close(p1[0], p1[1], p2[0], p2[1], ...)
          execve("grep","foo")

        [child3] wc -l
          open("out.txt", WRONLY|CREAT|APPEND) → dup2(fd, STDOUT)
          dup2(p2[0], STDIN)
          close(p1[0], p1[1], p2[0], p2[1], fd)
          execve("wc","-l")

        Chaque fils applique d’abord ses redirections (fichiers, pipes) via dup2, puis exécute le binaire. 
        Le parent ferme les extrémités inemployées pour éviter les blocages et récolte les statuts.
        13. Rôle de g_exit_status

            Mis à -1 avant un fork pour différencier les signaux enfants.

            Dans les handlers SIGINT/SIGQUIT, il prend immédiatement 130 ou 131 et redessine le prompt si l’interruption intervient en mode interactif.

            Après wait_all_update_status, il reflète le code de sortie de la dernière commande du pipeline et est recopié dans shell->exit_status pour la ligne suivante.

        14. Conclusion

        MINISHELL combine une architecture modulaire et une gestion rigoureuse des ressources :

            Lecture : readline → expansion → tokenisation.

            Préparation : redirections et heredocs stockés par commande.

            Exécution : builtin isolé (sans fork) ou pipeline (fork/exec) avec redirections.

            Synchronisation : gestion fine des signaux et propagation du code de retour.

            Nettoyage : chaque itération libère tokens, commandes, FD temporaires, garantissant un état sain pour la suivante.

        Grâce à cette structure, le projet reproduit l’essentiel du comportement d’un shell 
        POSIX et peut servir de base à des extensions plus poussées. Vous détenez désormais la compréhension exhaustive de MINISHELL — bonne maîtrise !



 flux de contrôle :

        ┌────────┐   start_shell   ┌───────────────┐
        │ main() │───────────────▶│ init/env/sign │
        └───┬────┘                 └──────┬────────┘
            │ read_loop                 │
            ▼                           ▼
          readline ────► process_input ──┬─ expand_input ──┬─ custom_split
                                         │                 └─ tokenisation & redirs
                                         │
                                         ├─ launch_process ──┬─ run_single_builtin?
                                         │                   └─ fork/exec/pipe
                                         ▼
                                    wait_all_update_status

_________________________________________________________________________________________
                      ┌────────────────────────────────────┐
                      │              main()                │
                      └───────────────┬────────────────────┘
                                      │ start_shell
                                      ▼
                            ┌──────────────────────┐
                            │      looping()       │
                            └──────────┬───────────┘
                                       │ readline
                                       ▼
                             ┌───────────────────┐
                             │ process_input()   │
                             └─┬────────────┬────┘
                   ┌───────────┘            └───────────────┐
                   ▼                                       ▼
              early_stage()                             expand_stage()
              - read_more                                - expand_input
              - add_history                              ▼
              - must_exit?                       parse_stage()
                   ▼                            - custom_split
                 run_stage()                    - attribute_token_type
              - launch_process                  - assign_redirs
              - cleanup_shell_iter              - build_cmd_list
                                                - alloc pids
                                                ▼
                                             launch_process()
                                             - run_single_builtin_if_alone ?
                                             - for each cmd:
                                                  pipe/fork
                                                  apply redirs
                                                  builtin or execve
                                             - wait_for_children



Exemple : cat < in.txt | grep foo | wc -l >> out.txt


                                    open("in.txt")          pipe()          pipe()            open("out.txt", APPEND)
                            stdin ───────────► cmd1 ──stdout─┬───► cmd2 ─stdout─┬───► cmd3 ─stdout─┬──► outfile
                                               ▲             │             │                   │
                                           dup2(infile,0)    │         dup2(pipe1[0],0)   dup2(pipe2[0],0)
                                                             │             │                   │
                                                          dup2(pipe1[1],1) │               dup2(outfile,1)
                                                             │         close/cleanup         close/cleanup



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


             Signal/Action,Effet pendant la saisie d'une commande,Effet pendant l'exécution d'une commande,Effet sur le shell lui-même
             Ctrl+C (SIGINT),Annule la saisie, retourne au prompt,Interrompt la commande en cours,Ne ferme pas le shell
             Ctrl+D (EOF),Envoie la commande pour exécution (comme Entrée),Indique la fin de l'entrée (EOF),Ferme le shell si le prompt est vide

Entrée utilisateur (readline)

readline(prompt) : lit une ligne avec édition (flèches, historique).
Shell-like : affiche ᕕ( ᐛ )ᕗ minishell$ et récupère ce que l’utilisateur tape.
Mini-ex : line = readline(prompt); if (line) add_history(line);

add_history(s) : ajoute s à l’historique (↑ ↓).

rl_clear_history() : vide l’historique (ex. builtin history -c).

rl_on_new_line(), rl_replace_line(buf,0), rl_redisplay() : utilitaires pour “ré-afficher proprement la ligne” après un signal ou un printf asynchrone (ex : \n suite à Ctrl-C).

Fichiers & I/O bas niveau

access(path, mode) : teste l’accès (existence/X_OK, R_OK…).
Shell-like : vérifier qu’un binaire dans $PATH est exécutable.

open(path, flags, mode) : ouvre/crée un fichier → fd.
Shell-like : redirections cmd > out (O_CREAT|O_TRUNC|O_WRONLY), >> (O_APPEND), < (O_RDONLY).

read(fd, buf, n) / close(fd) : lire / fermer un descripteur.
Shell-like : lire un heredoc, fermer les bouts de pipe inutiles.

unlink(path) : supprime un fichier.
Shell-like : nettoyer un fichier temporaire (rare si heredoc en pipe).

Processus

fork() : duplique le processus (parent/enfant).
Shell-like : chaque commande externe s’exécute dans un enfant.

execve(path, argv, envp) : remplace l’enfant par le programme.
Shell-like : exécuter /bin/ls avec l’environnement courant.

wait(&status) / waitpid(pid, &st, opts) : récupérer le code de fin.
Shell-like : attendre la fin d’un job, propager $?.

wait3/wait4 : variantes avec infos d’usage CPU/mémoire (optionnel).

exit(code) : termine le processus courant.
Shell-like : builtin exit, ou quitter l’enfant après execve échoué.

Signaux

signal(signum, handler) (basique) / sigaction(signum, &sa, …) (propre) : installer un gestionnaire (SIGINT, SIGQUIT…).
Shell-like : dans le parent, SIGINT (Ctrl-C) doit casser la ligne et rendre la main sans tuer le shell ; dans l’enfant, souvent on rétablit le comportement par défaut.

sigemptyset(&set), sigaddset(&set, SIGx) : manipuler des masques pour bloquer/débloquer des signaux.

kill(pid, sig) : envoyer un signal (ex. tuer un job).

Répertoire & chemins

getcwd(buf, size) : chemin courant → pour $PWD et pwd.

chdir(path) : changer de répertoire → builtin cd.

stat/lstat(path, &st), fstat(fd, &st) : infos fichier (type, mode…).
Shell-like : distinguer “Is a directory” vs “Permission denied” quand on tente d’exécuter un répertoire, suivre ou non les symlinks (lstat).

Pipes & duplication de descripteurs

pipe(int p[2]) : crée un tube p[0]=lecture, p[1]=écriture.
Shell-like : A | B | C → créer N-1 pipes, chaîner STDOUT→STDIN.

dup(oldfd) / dup2(oldfd, newfd) : dupliquer/rediriger un fd.
Shell-like : dup2(out_fd, STDOUT_FILENO) pour > file,
dup2(pipe_in, STDIN_FILENO) / dup2(pipe_out, STDOUT_FILENO) dans chaque maillon du pipeline.

Répertoires (API type ls)

opendir(path) → DIR*, readdir(dir) → struct dirent*, closedir(dir) : lister un répertoire.
Shell-like : utile pour l’auto-complétion (optionnel), ou émuler certaines commandes si tu implémentes un builtin style ls (non requis par minishell).

Erreurs & TTY

strerror(errno) : chaîne de l’erreur courante.

perror(prefix) : imprime prefix: strerror(errno) sur stderr.
Shell-like : messages fidèles à bash (ex. minishell: cd: x: No such file or directory).

isatty(fd) : teste si fd est un terminal.
Shell-like : adapter prompts, gestion interactive vs non-interactive (scripts).

ttyname(fd) : nom du tty, ttyslot() : index tty (rarement utile).

ioctl(fd, req, …) : opérations spécifiques terminal (avancé).
Shell-like : parfois pour query taille terminal, mais tu as déjà termcap/termios.

Environnement & variables

getenv("KEY") : lit une variable d’environnement.
Shell-like : récupérer PATH, HOME, etc. (Pour minishell, on maintient souvent notre copie d’environnement en liste chaînée et on génère envp pour execve.)

Contrôle du terminal (termios)

tcgetattr(fd, &term) / tcsetattr(fd, …, &term) : lire/écrire les flags du terminal.
Shell-like : gérer ECHOCTL (ne pas afficher ^C), désactiver/activer certains comportements pendant le heredoc.

Capabilities du terminal (termcap / terminfo)

tgetent(buf, term) : charge la base termcap pour $TERM.

tgetflag(name), tgetnum(name), tgetstr(name, &area) : capabilities booléennes, numériques, chaînes (p.ex. “cl” clear, “cm” cursor move).

tgoto(cap_cm, col, row) : construit une séquence de déplacement curseur.

tputs(str, affcnt, putc_fn) : “écrit” une capability (avec fonction putc).
Shell-like : si tu gères toi-même l’édition de ligne/affichage. Avec readline, c’est souvent inutile, mais utile pour mise en forme personnalisée, repositionnement du curseur, etc.



<p align="center" width="100">
    <img src=".Picture4rdme/minishell.png"/>
</p>
