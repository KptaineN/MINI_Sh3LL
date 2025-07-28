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



il faudra supprimer les quotes tout en respectant leur rôle de groupement. Par exemple :

    echo "hello world" → ["echo", "hello world"]

    echo 'hello'world → ["echo", "helloworld"]

    echo hello""world → ["echo", "helloworld"]

🛠️ Solution

Tu dois avoir une fonction dans ton parsing qui retire les quotes après avoir séparé les arguments et identifié les substrings.

Voici ce que tu dois faire :
1. ✅ Ajoute une fonction remove_quotes

char	*remove_quotes(const char *str)
{
	char	*result;
	int		i = 0, j = 0;
	char	quote = 0;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1); // au pire des cas : taille identique
	if (!result)
		return (NULL);

	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i]; // début quote
		else if (str[i] == quote)
			quote = 0; // fin quote
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

2. ✅ Applique remove_quotes sur les arguments de echo

Dans ton exécution de echo, juste avant d’imprimer les arguments, tu fais un remove_quotes() sur chaque :

void	execute_echo(t_ast *node)
{
	int		i = 1;
	char	*cleaned;

	while (node->args[i])
	{
		cleaned = remove_quotes(node->args[i]);
		if (cleaned)
		{
			printf("%s", cleaned);
			free(cleaned);
		}
		if (node->args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}



🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥

 ██    ██ █ ██    █ █ █████ █   █ █████ █     █       ██████ █████ █████ ██████ █████ █████  
 ███  ███ █ ███   █ █ █     █   █ █     █     █         ██   █     █       ██   █     █   ██
 █ ████ █ █ █ ██  █ █ █████ █████ ████  █     █         ██   ████  █████   ██   ████  █████  
 █  ██  █ █ █  ██ █ █     █ █   █ █     █     █         ██   █         █   ██   █     █   ██
 █      █ █ █   ███ █ █████ █   █ █████ █████ █████     ██   █████ █████   ██   █████ █   ██

🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥

———————————— builtins
Test   1: ✅ echo hello world
Test   2: ✅ echo "hello world"
Test   3: ✅ echo 'hello world'
Test   4: ✅ echo hello'world'
Test   5: ✅ echo hello""world
Test   6: ✅ echo ''
Test   7: ✅ echo "$PWD"
Test   8: ✅ echo '$PWD'
Test   9: ❌ echo "aspas ->'"
mini output = (aspas ->")
bash output = (aspas ->')
Test  10: ❌ echo "aspas -> ' "
mini output = (aspas -> )
bash output = (aspas -> ' )
Test  11: ❌ echo 'aspas ->"'
mini output = (aspas ->')
bash output = (aspas ->")
Test  12: ❌ echo 'aspas -> " '
mini output = (aspas -> )
bash output = (aspas -> " )
Test  13: ❌ echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<"
mini output = (> >> < bash_outfiles bash.supp bonus bonus_bonus builtins extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes README.md redirects syntax tester test_files wildcards ? [ ] | ; [ ] || && ( ) & # <<)
bash output = (> >> < bash_outfiles bash.supp bonus bonus_bonus builtins extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes README.md redirects syntax tester test_files wildcards ? [ ] | ; [ ] || && ( ) & # $ <<)
Test  14: ❌ echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<'
mini output = (> >> < bash_outfiles bash.supp bonus bonus_bonus builtins extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes README.md redirects syntax tester test_files wildcards ? [ ] | ; [ ] || && ( ) & # <<)
bash output = (> >> < bash_outfiles bash.supp bonus bonus_bonus builtins extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes README.md redirects syntax tester test_files wildcards ? [ ] | ; [ ] || && ( ) & # $ <<)
Test  15: ✅ echo "exit_code ->$? user ->$USER home -> $HOME"
Test  16: ❌ echo 'exit_code ->$? user ->$USER home -> $HOME'
mini output = (exit_code ->0 user ->nkiefer home -> /home/nkiefer)
bash output = (exit_code ->$? user ->$USER home -> $HOME)
Test  17: ❌ echo "$"
mini output = ()
bash output = ($)
Test  18: ✅ echo '$'
Test  19: ❌ echo $
mini output = ()
bash output = ($)
Test  20: ✅ echo $?
Test  21: ✅ echo $?HELLO
Test  22: ✅ pwd
Test  23: ✅ pwd oi
Test  24: ✅ export hello
Test  25: ✅ export HELLO=123
Test  26: ❌ export A-
mini output = (minishell: export: `A-': not a valid identifier)
bash output = ()
mini error = ()
bash error = ( not a valid identifier)
Test  27: ✅ export HELLO=123 A
Test  28: ❌ export HELLO="123 A-"
mini output = (minishell: export: `A-"': not a valid identifier)
bash output = ()
mini exit code = 1
bash exit code = 0
Test  29: ✅ export hello world
Test  30: ❌ export HELLO-=123
mini output = (minishell: export: `HELLO-': not a valid identifier)
bash output = ()
mini error = ()
bash error = ( not a valid identifier)
Test  31: ❌ export =
mini output = (minishell: export: `': not a valid identifier)
bash output = ()
mini error = ()
bash error = ( not a valid identifier)
Test  32: ❌ export 123
mini output = (minishell: export: `123': not a valid identifier)
bash output = ()
mini error = ()
bash error = ( not a valid identifier)
Test  33: ✅ unset
Test  34: ✅ unset HELLO
Test  35: ✅ unset HELLO1 HELLO2
Test  36: ✅ unset HOME
Test  37: ✅ unset PATH
Test  38: ✅ unset SHELL
Test  39: ✅⚠️  cd $PWD
mini error = ( No such file or directory)
bash error = ( too many arguments)
Test  40: ✅⚠️  cd $PWD hi
mini error = ( No such file or directory)
bash error = ( too many arguments)
Test  41: ✅ cd 123123
Test  42: ✅ exit 123
Test  43: ✅ exit 298
Test  44: ✅ exit +100
Test  45: ❌ exit "+100"
mini exit code = 255
bash exit code = 100
mini error = ( numeric argument required)
bash error = ()
Test  46: ❌ exit +"100"
mini exit code = 255
bash exit code = 100
mini error = ( numeric argument required)
bash error = ()
Test  47: ✅ exit -100
Test  48: ❌ exit "-100"
mini exit code = 255
bash exit code = 156
mini error = ( numeric argument required)
bash error = ()
Test  49: ❌ exit -"100"
mini exit code = 255
bash exit code = 156
mini error = ( numeric argument required)
bash error = ()
Test  50: ❌ exit hello
mini exit code = 255
bash exit code = 2
Test  51: ✅ exit 42 world
Test  52: ✅  
———————————— pipes
Test  53: ❌ env | sort | grep -v SHLVL | grep -v ^_
mini output = (SHELL=/bin/zsh SESSION_MANAGER=local/c1r5s2.42luxembourg.lu:@/tmp/.ICE-unix/4047754,unix/c1r5s2.42luxembourg.lu:/tmp/.ICE-unix/4047754 QT_ACCESSIBILITY=1 COLORTERM=truecolor XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg SSH_AGENT_LAUNCHER=gnome-keyring XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session32 XDG_MENU_PREFIX=gnome- GNOME_DESKTOP_SESSION_ID=this-is-deprecated GTK_IM_MODULE=ibus LANGUAGE=en SSH_AUTH_SOCK=/run/user/101479/keyring/ssh XMODIFIERS=@im=ibus DESKTOP_SESSION=ubuntu FT_HOOK_NAME=login-user GTK_MODULES=gail:atk-bridge DBUS_STARTER_BUS_TYPE=session FT_HOOK_PATHNAME=login-user.d KRB5CCNAME=FILE:/tmp/krb5cc_101479_o23JKP PWD=/home/nkiefer/Documents/MINISHELL/git/MINISHELL NRICO-NOE/minishell_tester LOGNAME=nkiefer XDG_SESSION_DESKTOP=ubuntu XDG_SESSION_TYPE=x11 GPG_AGENT_INFO=/run/user/101479/gnupg/S.gpg-agent:0:1 SYSTEMD_EXEC_PID=4047754 XAUTHORITY=/home/nkiefer/.Xauthority XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/nkiefer GDM_LANG=en HOME=/home/nkiefer LANG=en_US.UTF-8 XDG_CURRENT_DESKTOP=ubuntu:GNOME VTE_VERSION=6800 XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0 GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/96104e1e_b2fd_4b07_985f_d479cb16bf3b XDG_SESSION_CLASS=user TERM=xterm-256color LIBVIRT_DEFAULT_URI=qemu:///system USER=nkiefer GNOME_TERMINAL_SERVICE=:1.161 DISPLAY=:0 SHLVL=1 QT_IM_MODULE=ibus DBUS_STARTER_ADDRESS=unix:path=/run/user/101479/bus,guid=c88ab0589427993aa239aa8d6866fd5b XDG_RUNTIME_DIR=/run/user/101479 DOCKER_HOST=unix:///run/user/101479/docker.sock XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/home/nkiefer/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop PATH=/home/nkiefer/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/nkiefer/.local/bin GDMSESSION=ubuntu DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/101479/bus,guid=c88ab0589427993aa239aa8d6866fd5b OLDPWD=/home/nkiefer/Documents/MINISHELL/git/MINISHELL NRICO-NOE _=../minishell)
bash output = (COLORTERM=truecolor DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/101479/bus,guid=c88ab0589427993aa239aa8d6866fd5b DBUS_STARTER_ADDRESS=unix:path=/run/user/101479/bus,guid=c88ab0589427993aa239aa8d6866fd5b DBUS_STARTER_BUS_TYPE=session DESKTOP_SESSION=ubuntu DISPLAY=:0 DOCKER_HOST=unix:///run/user/101479/docker.sock FT_HOOK_NAME=login-user FT_HOOK_PATHNAME=login-user.d GDM_LANG=en GDMSESSION=ubuntu GNOME_DESKTOP_SESSION_ID=this-is-deprecated GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/96104e1e_b2fd_4b07_985f_d479cb16bf3b GNOME_TERMINAL_SERVICE=:1.161 GPG_AGENT_INFO=/run/user/101479/gnupg/S.gpg-agent:0:1 GTK_IM_MODULE=ibus GTK_MODULES=gail:atk-bridge HOME=/home/nkiefer KRB5CCNAME=FILE:/tmp/krb5cc_101479_o23JKP LANG=en_US.UTF-8 LANGUAGE=en LIBVIRT_DEFAULT_URI=qemu:///system LOGNAME=nkiefer OLDPWD=/home/nkiefer/Documents/MINISHELL/git/MINISHELL NRICO-NOE PATH=/home/nkiefer/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/nkiefer/.local/bin PWD=/home/nkiefer/Documents/MINISHELL/git/MINISHELL NRICO-NOE/minishell_tester QT_ACCESSIBILITY=1 QT_IM_MODULE=ibus SESSION_MANAGER=local/c1r5s2.42luxembourg.lu:@/tmp/.ICE-unix/4047754,unix/c1r5s2.42luxembourg.lu:/tmp/.ICE-unix/4047754 SHELL=/bin/zsh SSH_AGENT_LAUNCHER=gnome-keyring SSH_AUTH_SOCK=/run/user/101479/keyring/ssh SYSTEMD_EXEC_PID=4047754 TERM=xterm-256color USER=nkiefer VTE_VERSION=6800 XAUTHORITY=/home/nkiefer/.Xauthority XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg XDG_CURRENT_DESKTOP=ubuntu:GNOME XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/home/nkiefer/.local/share/flatpak/exports/share:/var/lib/flatpak/exports/share:/usr/local/share:/usr/share:/var/lib/snapd/desktop XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/nkiefer XDG_MENU_PREFIX=gnome- XDG_RUNTIME_DIR=/run/user/101479 XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0 XDG_SESSION_CLASS=user XDG_SESSION_DESKTOP=ubuntu XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session32 XDG_SESSION_TYPE=x11 XMODIFIERS=@im=ibus)
Test  54: ❌ cat ./test_files/infile_big | grep oi
mini output = ()
bash output = (was going to happen next. First, she tried to look down and make out disappointment it was empty: she did not like to drop the jar for fear not going to do _that_ in a hurry. “No, I’ll look first,” she said, “and see whether it’s marked ‘_poison_’ or not”; for she had read bottle marked “poison,” it is almost certain to disagree with you, However, this bottle was _not_ marked “poison,” so Alice ventured to brightened up at the thought that she was now the right size for going waited for a few minutes to see if she was going to shrink any further: said Alice to herself, “in my going out altogether, like a candle. I After a while, finding that nothing more happened, she decided on going Rabbit came near her, she began, in a low, timid voice, “If you please, to repeat it, but her voice sounded hoarse and strange, and the words now about two feet high, and was going on shrinking rapidly: she soon dropped it hastily, just in time to avoid shrinking away altogether. “Not like cats!” cried the Mouse, in a shrill, passionate voice. “Would trembling voice, “Let us get to the shore, and then I’ll tell you my “What I was going to say,” said the Dodo in an offended tone, “was, “But who is to give the prizes?” quite a chorus of voices asked. “Why, _she_, of course,” said the Dodo, pointing to Alice with one The next thing was to eat the comfits: this caused some noise and the others all joined in chorus, “Yes, please do!” but the Mouse only doesn’t suit my throat!” and a Canary called out in a trembling voice doing out here? Run home this moment, and fetch me a pair of gloves and at once in the direction it pointed to, without trying to explain the “How queer it seems,” Alice said to herself, “to be going messages for gloves, and was just going to leave the room, when her eye fell upon a she heard a voice outside, and stopped to listen. “Mary Ann! Mary Ann!” said the voice. “Fetch me my gloves this moment!” Next came an angry voice—the Rabbit’s—“Pat! Pat! Where are you?” And then a voice she had never heard before, “Sure then I’m here! Digging rumbling of little cartwheels, and the sound of a good many voices all then the Rabbit’s voice along—“Catch him, you by the hedge!” then silence, and then another confusion of voices—“Hold up his head—Brandy Last came a little feeble, squeaking voice, (“That’s Bill,” thought “We must burn the house down!” said the Rabbit’s voice; and Alice addressed her in a languid, sleepy voice. came different!” Alice replied in a very melancholy voice. By the use of this ointment—one shilling the box— going to dive in among the leaves, which she found to be nothing but Pigeon, raising its voice to a shriek, “and just as I was thinking I going to be, from one minute to another! However, I’ve got back to my are; secondly, because they’re making such a noise inside, no one could noise going on within—a constant howling and sneezing, and every now “Oh, _please_ mind what you’re doing!” cried Alice, jumping up and down (In which the cook and the baby joined): ear and left foot, so as to prevent its undoing itself,) she carried it No, there were no tears. “If you’re going to turn into a pig, my dear,” eyes, “Of course, of course; just what I was going to remark myself.” quarrelled last March—just before _he_ went mad, you know—” (pointing hoarse, feeble voice: “I heard every word you fellows were saying.” The Dormouse had closed its eyes by this time, and was going off into a neither of the others took the least notice of her going, though she voice, “Why the fact is, you see, Miss, this here ought to have been a you see, Miss, we’re doing our best, afore she comes, to—” At this “And who are _these?_” said the Queen, pointing to the three gardeners “Get up!” said the Queen, in a shrill, loud voice, and the three turning to the rose-tree, she went on, “What _have_ you been doing “May it please your Majesty,” said Two, in a very humble tone, going “Come on, then!” roared the Queen, and Alice joined the procession, “It’s—it’s a very fine day!” said a timid voice at her side. She was “Get to your places!” shouted the Queen in a voice of thunder, and had got its neck nicely straightened out, and was going to give the going to begin again, it was very provoking to find that the hedgehog “How do you like the Queen?” said the Cat in a low voice. “Who _are_ you talking to?” said the King, going up to Alice, and Alice thought she might as well go back, and see how the game was going on, as she heard the Queen’s voice in the distance, screaming with a large crowd collected round it: there was a dispute going on between thing before, and he wasn’t going to begin at _his_ time of life. startled when she heard her voice close to her ear. “You’re thinking “The game’s going on rather better now,” she said, by way of keeping up But here, to Alice’s great surprise, the Duchess’s voice died away, “A fine day, your Majesty!” the Duchess began in a low, weak voice. about half no time! Take your choice!” The Duchess took her choice, and was gone in a moment. As they walked off together, Alice heard the King say in a low voice, sea. The master was an old Turtle—we used to call him Tortoise—” “Why did you call him Tortoise, if he wasn’t one?” Alice asked. “We called him Tortoise because he taught us,” said the Mock Turtle Fainting in Coils.” two sobs choked his voice. “Same as if he had a bone in his throat,” the back. At last the Mock Turtle recovered his voice, and, with tears “Change lobsters again!” yelled the Gryphon at the top of its voice. Turtle, suddenly dropping his voice; and the two creatures, who had “There’s a porpoise close behind us, and he’s treading on my tail. They are waiting on the shingle—will you come and join the dance? Will you, won’t you, will you, won’t you, will you join the dance? Will you, won’t you, will you, won’t you, won’t you join the dance? Said he thanked the whiting kindly, but he would not join the dance. Would not, could not, would not, could not, would not join the dance. Would not, could not, would not, could not, could not join the dance. Then turn not pale, beloved snail, but come and join the dance. Will you, won’t you, will you, won’t you, will you join the dance? Will you, won’t you, will you, won’t you, won’t you join the dance?” “Boots and shoes under the sea,” the Gryphon went on in a deep voice, running on the song, “I’d have said to the porpoise, ‘Keep back, wise fish would go anywhere without a porpoise.” and told me he was going a journey, I should say ‘With what porpoise?’” Alice a little timidly: “but it’s no use going back to yesterday, “Stand up and repeat ‘’_Tis the voice of the sluggard_,’” said the “’Tis the voice of the Lobster; I heard him declare, His voice has a timid and tremulous sound.] wrong, and she went on in a trembling voice:— The Mock Turtle sighed deeply, and began, in a voice sometimes choked they doing?” Alice whispered to the Gryphon. “They can’t have anything “Stupid things!” Alice began in a loud, indignant voice, but she “I’m a poor man, your Majesty,” the Hatter began, in a trembling voice, The King looked anxiously at the White Rabbit, who said in a low voice, nearly out of sight, he said in a deep voice, “What are tarts made of?” “Treacle,” said a sleepy voice behind her. little voice, the name “Alice!” “The trial cannot proceed,” said the King in a very grave voice, “until verdict,” he said to the jury, in a low, trembling voice. “Why, there they are!” said the King triumphantly, pointing to the “Off with her head!” the Queen shouted at the top of her voice. Nobody looking up into hers—she could hear the very tones of her voice, and shared their never-ending meal, and the shrill voice of the Queen cries to the voice of the shepherd boy—and the sneeze of the baby, the shriek of the Gryphon, and all the other queer noises, would change unenforceability of any provision of this agreement shall not void the)
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  55: ✅ cat minishell.h | grep ");"$
Test  56: ❌ export GHOST=123 | env | grep GHOST
mini output = (minishell: export: `|': not a valid identifier minishell: export: `|': not a valid identifier)
bash output = ()
———————————— redirects
Test  57: ❌ grep hi <./test_files/infile
mini output = ()
bash output = (hi)
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  58: ❌ grep hi "<infile" <         ./test_files/infile
mini exit code = 1
bash exit code = 2
Test  59: ❌ echo hi < ./test_files/infile bye bye
mini output = (hi < ./test_files/infile bye bye)
bash output = (hi bye bye)
Test  60: ❌ grep hi <./test_files/infile_big <./test_files/infile
mini output = ()
bash output = (hi)
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  61: ❌ echo <"./test_files/infile" "bonjour       42"
mini output = (<./test_files/infile bonjour 42)
bash output = (bonjour 42)
Test  62: ❌ cat <"./test_files/file name with spaces"
mini output = ()
bash output = (😈 😈 😈 This will break your minishell 😈 😈 😈)
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  63: ❌ cat <./test_files/infile_big ./test_files/infile
mini output = ()
bash output = (hi hello world 42)
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  64: ✅ cat <"1""2""3""4""5"
Test  65: ❌ echo <"./test_files/infile" <missing <"./test_files/infile"
mini output = (<./test_files/infile <missing <./test_files/infile)
bash output = ()
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test  66: ❌ echo <missing <"./test_files/infile" <missing
mini output = (<missing <./test_files/infile <missing)
bash output = ()
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( No such file or directory)
Test  67: ❌ cat <"./test_files/infile"
mini output = ()
bash output = (hi hello world 42)
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  68: ❌ echo <"./test_files/infile_big" | cat <"./test_files/infile"
mini output = (<./test_files/infile_big | cat <./test_files/infile)
bash output = (hi hello world 42)
Test  69: ❌ echo <"./test_files/infile_big" | cat "./test_files/infile"
mini output = (<./test_files/infile_big | cat ./test_files/infile)
bash output = (hi hello world 42)
Test  70: ❌ echo <"./test_files/infile_big" | echo <"./test_files/infile"
mini output = (<./test_files/infile_big | echo <./test_files/infile)
bash output = ()
Test  71: ❌ echo hi | cat <"./test_files/infile"
mini output = (hi | cat <./test_files/infile)
bash output = (hi hello world 42)
Test  72: ❌ echo hi | cat "./test_files/infile"
mini output = (hi | cat ./test_files/infile)
bash output = (hi hello world 42)
Test  73: ❌ cat <"./test_files/infile" | echo hi
mini output = ()
bash output = (hi)
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ( Broken pipe)
Test  74: ❌ cat <"./test_files/infile" | grep hello
mini output = ()
bash output = (hello)
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  75: ❌ cat <"./test_files/infile_big" | echo hi
mini output = ()
bash output = (hi)
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ( Broken pipe)
Test  76: ✅ cat <missing
Test  77: ❌ cat <missing | cat
mini exit code = 1
bash exit code = 0
Test  78: ❌ cat <missing | echo oi
mini output = ()
bash output = (oi)
mini exit code = 1
bash exit code = 0
Test  79: ❌ cat <missing | cat <"./test_files/infile"
mini output = ()
bash output = (hi hello world 42)
mini exit code = 1
bash exit code = 0
Test  80: ❌ echo <123 <456 hi | echo 42
mini output = (<123 <456 hi | echo 42)
bash output = (42)
mini error = ()
bash error = ( No such file or directory)
Test  81: ❌ ls >./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  82: ❌ ls >         ./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  83: ❌ echo hi >         ./outfiles/outfile01 bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi bye
mini output = (hi > ./outfiles/outfile01 bye)
bash output = ()
Test  84: ❌ ls >./outfiles/outfile01 >./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  85: ❌ ls >./outfiles/outfile01 >./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test  86: ❌ ls >"./outfiles/outfile with spaces"
Only in ./bash_outfiles: outfile with spaces
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  87: ❌ ls >"./outfiles/outfile""1""2""3""4""5"
Only in ./bash_outfiles: outfile12345
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  88: ❌ ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02"
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test  89: ✅⚠️  ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test  90: ❌ cat <"./test_files/infile" >"./outfiles/outfile01"
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
hello
world
42
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test  91: ❌ echo hi >./outfiles/outfile01 | echo bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini output = (hi >./outfiles/outfile01 | echo bye)
bash output = (bye)
Test  92: ❌ echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini output = (hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye)
bash output = (bye)
Test  93: ❌ echo hi | echo >./outfiles/outfile01 bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bye
mini output = (hi | echo >./outfiles/outfile01 bye)
bash output = ()
Test  94: ❌ echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bye
mini output = (hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02)
bash output = ()
Test  95: ❌ echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
bye
mini output = (hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02)
bash output = ()
Test  96: ❌ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini output = (hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye)
bash output = (bye)
mini error = ()
bash error = ( Permission denied)
Test  97: ❌ echo hi >./test_files/invalid_permission | echo bye
mini output = (hi >./test_files/invalid_permission | echo bye)
bash output = (bye)
mini error = ()
bash error = ( Permission denied)
Test  98: ❌ echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye
mini output = (hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye)
bash output = (bye)
mini error = ()
bash error = ( Permission denied)
Test  99: ❌ echo hi | echo bye >./test_files/invalid_permission
mini output = (hi | echo bye >./test_files/invalid_permission)
bash output = ()
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 100: ❌ echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini output = (hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission)
bash output = ()
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 101: ❌ echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01
mini output = (hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01)
bash output = ()
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 102: ✅⚠️  cat <"./test_files/infile" >./test_files/invalid_permission
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 103: ✅⚠️  cat >./test_files/invalid_permission <"./test_files/infile"
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 104: ✅ cat <missing >./outfiles/outfile01
Test 105: ❌ cat >./outfiles/outfile01 <missing
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
Test 106: ✅ cat <missing >./test_files/invalid_permission
Test 107: ✅⚠️  cat >./test_files/invalid_permission <missing
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 108: ❌ cat >./outfiles/outfile01 <missing >./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
Test 109: ❌ ls >>./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test 110: ❌ ls >>      ./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test 111: ❌ ls >>./outfiles/outfile01 >./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test 112: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test 113: ❌ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test 114: ❌ ls >>./outfiles/outfile01 >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bash_outfiles
bash.supp
bonus
bonus_bonus
builtins
extras
local.supp
loop.out
manual_tests
mini_outfiles
os_specific
outfiles
pipes
README.md
redirects
syntax
tester
test_files
wildcards
mini exit code = 1
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test 115: ✅⚠️  ls >>./test_files/invalid_permission
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 116: ✅⚠️  ls >>./test_files/invalid_permission >>./outfiles/outfile01
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 117: ❌ ls >>./outfiles/outfile01 >>./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 118: ❌ ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 119: ✅ ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02
Test 120: ✅⚠️  ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing
mini error = ( No such file or directory)
bash error = ( Permission denied)
Test 121: ❌ echo hi >>./outfiles/outfile01 | echo bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini output = (hi >>./outfiles/outfile01 | echo bye)
bash output = (bye)
Test 122: ❌ echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
mini output = (hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye)
bash output = (bye)
Test 123: ❌ echo hi | echo >>./outfiles/outfile01 bye
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bye
mini output = (hi | echo >>./outfiles/outfile01 bye)
bash output = ()
Test 124: ❌ echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
bye
mini output = (hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02)
bash output = ()
Test 125: ❌ echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02
Only in ./bash_outfiles: outfile01
Only in ./bash_outfiles: outfile02
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
hi
bye
mini output = (hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02)
bash output = ()
Test 126: ❌ echo hi >>./test_files/invalid_permission | echo bye
mini output = (hi >>./test_files/invalid_permission | echo bye)
bash output = (bye)
mini error = ()
bash error = ( Permission denied)
Test 127: ❌ echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye
mini output = (hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye)
bash output = (bye)
mini error = ()
bash error = ( Permission denied)
Test 128: ❌ echo hi | echo bye >>./test_files/invalid_permission
mini output = (hi | echo bye >>./test_files/invalid_permission)
bash output = ()
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 129: ❌ echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/*': No such file or directory
bash outfiles:
mini output = (hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission)
bash output = ()
mini exit code = 0
bash exit code = 1
mini error = ()
bash error = ( Permission denied)
Test 130: ✅ cat <minishell.h>./outfiles/outfile
Test 131: ❌ cat <minishell.h|ls
mini output = ()
bash output = (bash_outfiles bash.supp bonus bonus_bonus builtins extras local.supp loop.out manual_tests mini_outfiles os_specific outfiles pipes README.md redirects syntax tester test_files wildcards)
mini exit code = 1
bash exit code = 0
———————————— extras
Test 132: ✅  
Test 133: ❌ $PWD
mini exit code = 1
bash exit code = 127
Test 134: ❌ $EMPTY
mini exit code = 127
bash exit code = 0
mini error = ( (null))
bash error = ()
Test 135: ✅ $EMPTY echo hi
Test 136: ❌ ./test_files/invalid_permission
mini exit code = 1
bash exit code = 126
Test 137: ❌ ./missing.out
mini exit code = 1
bash exit code = 127
Test 138: ❌ missing.out
mini exit code = 1
bash exit code = 127
mini error = ( No such file or directory)
bash error = ( command not found)
Test 139: ❌ "aaa"
mini exit code = 1
bash exit code = 127
mini error = ( No such file or directory)
bash error = ( command not found)
Test 140: ❌ test_files
mini exit code = 1
bash exit code = 127
mini error = ( Permission denied)
bash error = ( command not found)
Test 141: ❌ ./test_files
mini exit code = 1
bash exit code = 126
mini error = ( Permission denied)
bash error = ( Is a directory)
Test 142: ❌ /test_files
mini exit code = 1
bash exit code = 127
Test 143: ❌ minishell.h
mini exit code = 1
bash exit code = 127
mini error = ( No such file or directory)
bash error = ( command not found)
Test 144: ✅⚠️  $
mini error = ( (null))
bash error = ( command not found)
Test 145: ❌ $?
mini exit code = 1
bash exit code = 127
mini error = ( No such file or directory)
bash error = ( command not found)
Test 146: ❌ README.md
mini exit code = 1
bash exit code = 127
mini error = ( Permission denied)
bash error = ( command not found)
50/146
😭 😭 😭
c1r5s2%

<p align="center" width="100">
    <img src=".Picture4rdme/minishell.png"/>
</p>
