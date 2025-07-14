#include "../../include/parsking.h"


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


/*
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	const char *arg = "errors.err>errors.err>>errors.err";//"echo<system.log"; //"\"so \\\"hima\\\"ma\\\" bru\\\"";//"ls -la";
	t_shell *shell;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return 0;
	memset(shell, 0, sizeof(t_shell));
	init_idx(shell);

	shell->env = set_linked_path(envp);
	printf("first env:\t%s\n", (char *)shell->env->content); // debug
	
	init_all_t_arr(shell);
	print_dic(shell->oper);

	shell->parsed_args = custom_split(arg, shell);

	attribute_token_type(shell);
	print_all_parts(shell);

	launch_process(shell);
	

    return (0);
}*/
	