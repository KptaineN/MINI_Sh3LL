/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:45:24 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/28 16:08:26 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mini.h"


/*
Ici il y a le premier parsing qui est fusioné avec la tokenisation et subtokenisation (mon invention)
parsing -> decouper,	tokenisation -> attribution du type "WORD,PIPE,REDIREC,..."
subtokenisaiton -> pour une string, decoupage des regions "UNQUOTED,SINGLE QUOTED,DOUBLE QUOTED"

STRUCTURE: 	Tout est mis en ARRAY comme tu peux voir dans la struct t_shell on a: int token_count, t_token *tokens; (longeur array, array de)
			Pareil pour les subtoken: int n_parts, t_subtoken *parts; (longeur array, array de)

*/




/*
Je te facilite la vie en donnant plus d'info dans le parsing:

cette commande ->		echo "$USER"'$USER'

vue depuis l'ordi 		"echo \"$USER\"\'$USER\'"

a comme resultat		Paprika’$USER’	(le premier se fait expand, l'autre non (double quote/single quote))

Donc dans le tokenisation j'ai fait que:access

"echo \"$USER\"\'$USER\'" -> token "echo", token "\"$USER\"\’$USER\’"

subtokens de echo
{
	typedef struct s_token
	{
		char			type;		WORD
		char			*value;		"echo"
		int				n_parts;	1 subtoken
		t_subtoken		*parts;		
	}					t_token;
	typedef struct s_subtoken
	{
		t_quote_type	UNQUOTED
		char *p; 		"echo"
		int len; 		4
	}					t_subtoken;
}
subtokens de "\"$USER\"\’$USER\’"
{
	typedef struct s_token
	{
		char			type;		WORD
		char			*value;		"\"$USER\"\’$USER\’"
		int				n_parts;	2 subtoken
		t_subtoken		*parts;		
	}					t_token;
	typedef struct s_subtoken
	{
		t_quote_type	DOUBLE QUOTED
		char *p; 		"$USER\"\’$USER\’"    pointeur
		int len; 		5
	}					t_subtoken;
	typedef struct s_subtoken
	{
		t_quote_type	SINGLE QUOTED
		char *p; 		"$USER\'"
		int len; 		5
	}					t_subtoken;
}

Donc les pointeur pointe a apres les quotes, et chaque partie est catégorisé comme ca tu dois pas le faire pares :)
*/

void init_idx(t_shell *shell)
{
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->fd_in  = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//const char *arg = "cat < cmd.c < cmd.c";
	const char *arg = "cat < cmd.c | grep eganassi"; 
	//"wc -l < temp.txt | grep 1 << EOF" ;//"echo<system.log"; //"\"so \\\"hima\\\"ma\\\" bru\\\"";//"ls -la";
	t_shell *shell;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return 0;
	memset(shell, 0, sizeof(t_shell));
	init_idx(shell);

	shell->env = set_linked_path(envp);
	printf("first env:\t%s\n", (char *)shell->env->content); // debug
	
	init_all_t_arr(shell);
	//print_dic(shell->oper);

	shell->parsed_args = custom_split(arg, shell);

	attribute_token_type(shell);
	//print_all_parts(shell);
	print_all_head_cmd(shell);
	//char **exp_cmd = expand_cmd(shell->tokens, shell->env);
	//printStringArray("cmd: ", (const char **)exp_cmd);
	shell->pids = malloc(sizeof(pid_t)*shell->n_cmd);
	if (!shell->pids)
		perror("MALLOC pids");

	//execv(find_command_path("ls", shell->env), (char *[]){"ls", NULL});	
	//test execute add path pid
	//replace_or_add(&shell->env,"P=","PID=4242");


	/*
	DA FARE:

	- launch process - 
	Devo leggere i file nei processi senza fare un force quit su gli altri
	tipo: cat < non_existing.txt | grep "test" << EOF
	il heredoc deve essere aperto al momento del lancio del processo [grep "test" << EOF]
	ed normalmente grep test eseguisce grep sulla lista di filedescriptor 
	{stderror 'std che dub2 con non_existing', 'heredoc'} 
	quindi normalemente il grep di 'heredoc' continua sul prossimo pipe
	*/

	/*
	int filefd_one= open("another.txt",O_RDONLY);
	int filefd_two= open("another.txt",O_RDONLY);
	
	dup2(filefd_one, STDIN_FILENO);
	dup2(filefd_two, STDIN_FILENO);
	t_cmd_red *container = shell->cmd_head->content;
	t_arr * cmd = container->cmd;
	t_token *one_token = cmd->arr[0];
	execute(shell, one_token);
	*/
	    
	/*
	t_token * a = NULL;
	a = unwrap_token(shell);
	shell->cmd_tail = shell->cmd_tail->next;
	t_token *b = NULL;
	b = unwrap_token(shell);
	(void) a;
	(void) b;
	*/

	launch_process(shell);

    return (0);
}
	

/*
list commands:

 - ls 42 > output.txt | ls nonex >> output.txt 2>&1
 - cat output.txt                                  
42-EXAM
C05
ls: cannot access 'nonex': No such file or directory

➜  ~ ls 42 nonex > output.txt 2>&1 
➜  ~ cat output.txt 
ls: cannot access 'nonex': No such file or directory
42:
42-EXAM
C05

➜  ~ cat < another.txt | grep "babygirl" < another.txt > output.txt 2>&1
➜  ~ cat < another.txt | grep "babygirl" < another.txt > output.txt     
➜  ~ cat output.txt 
2 babygirl
2 babygirl
*/

