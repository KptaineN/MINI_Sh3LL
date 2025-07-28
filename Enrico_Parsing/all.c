
#include "mini.h"

int ft_echo(void *shell, int token_idx)
{
    (void) shell;
    (void) token_idx;
    return 0;
}

int ft_cd(void *shell, int token_idx)
{
    (void) shell;
    (void) token_idx;
    return 0;
}

int ft_pwd(void *shell, int token_idx)
{
    (void) shell;
    (void) token_idx;
    return 0;
}

int ft_export(void *shell, int token_idx)
{
    (void) shell;
    (void) token_idx;
    return 0;
}

int ft_unset(void *shell, int token_idx)
{
    (void) shell;
    (void) token_idx;
    return 0;
}

int ft_env(void *shell, int token_idx)
{
    (void) shell;
    (void) token_idx;
    return 0;
}

int ft_exit(void *shell, int token_idx)
{
    (void) shell;
    (void) token_idx;
    return 0;
}


#include "mini.h"

bool is_command(char *str, t_list *env)
{
    char *cmd_path;
    cmd_path = find_command_path(str, env);
	if (cmd_path)
        return 0;
    free(cmd_path);
    return 1;
}

// normal strdup - get rid of later when LIBFT
char *ft_strdup(const char *s1)
{
    char *dup;
    int len;
    int i;

    if (!s1)
        return (NULL);
    
    len = 0;
    while (s1[len])
        len++;
    
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    
    i = 0;
    while (i < len)
    {
        dup[i] = s1[i];
        i++;
    }
    dup[i] = '\0';
    
    return (dup);
}

/* Cette fonciton sert a une partie importante de minishell
essaye echo "hello
*/
bool escape_check(const char *str ,int idx)
{
	bool i = 1;
	if (idx != 0)
	{
		idx--;
		while(idx != 0 && str[idx] =='\\')
		{	i^=1;
			idx--;
		}
		if (i)
			return 1;
		return 0;
	}
	return 1;
}

/*
compte le nombre argument pour les commandes shell
ex: "ls -la > grep "Noe!" file.txt"
-> "ls" "-la" ">" "grep" "\"Noe!\"" "file.txt"

gere les cas ou: "\"hello\'mamman\'\"" -> "hello\'mamman\'" (expansion apres pour toi)
*/
static int	count_arg(const char *str, t_shell *shell)//, int *sub_n)
{
	int		count;
	bool	in_single_quote;
	bool	in_double_quote;
	bool	in_word;
	int idx_oper;
	//t_quote_type current_quote = QUOTE_NONE;
	
	count = 0;
	in_single_quote = false;
	in_double_quote = false;
	in_word = false;
	int i = 0;
	while(str[i])
	{
		char c = str[i];
		(void) c;
		idx_oper = is_in_t_arr_dic_str(shell->oper, (char *)&str[i]);
		if (str[i] == '\'' && !in_double_quote && escape_check(str,i))
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote && escape_check(str,i))
			in_double_quote = !in_double_quote;	
		else if (str[i] == ' ' && !in_single_quote && !in_double_quote)
		{
			if (in_word)
			{
				in_word = false;
				count++;
			}
		}
		else if (idx_oper != -1 && !in_single_quote && !in_double_quote)
		{						// is a oper
			in_word = false;
			count++;
			i+=strlen((char *)((t_dic *)shell->oper->arr[idx_oper])->key)-1;
		}
		else if (!in_word)
		{	
			in_word = true;
		}
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

// Function to extract a single token
static char	*extract_arg(const char *str, int *start, t_shell *shell)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		token_start;
	int		token_end;
	int		token_len;
	char	*token;

	int idx_oper_one;
	int oper_ad = 0;

	in_single_quote = false;
	in_double_quote = false;
	token_start = *start;
	token_end = *start;
	// Skip leading spaces
	while (str[token_start] && str[token_start] == ' ')
		token_start++;
	if (!str[token_start])
		return (NULL);
	token_end = token_start;
	// Find the end of the token
	const char * tmp;
	tmp = (char *)shell->oper->arr[6];
	(void)tmp;
	while (str[token_end])
	{	
		char c = str[token_end];
		if (str[token_end] == '\'' && !in_double_quote && escape_check(str,token_end))
			in_single_quote = !in_single_quote;
		else if (str[token_end] == '"' && !in_single_quote && escape_check(str,token_end))
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote)
		{
			if (str[token_end] == ' ')
				break ;
			idx_oper_one = is_in_t_arr_dic_str(shell->oper, &str[token_end]);
			if (idx_oper_one != -1)
			{	
				oper_ad = strlen((const char *)((t_dic *)shell->oper->arr[idx_oper_one])->key);
				break;
			}
			if (str[token_end+1] != 0 && is_in_t_arr_dic_str(shell->oper, &str[token_end+1]) != -1)
			{	
				oper_ad = 1;
				break;
			}
		}
		token_end++;
		(void)c;
	}
	/*  A implementer le quote> et la terminaison
	➜  ~ echo 'so"
		quote> sdf"
		quote> 
		➜  ~ echo 'so"
		sdf"  
		quote> '
		so"
		sdf"
	*/
	//if (in_double_quote || in_single_quote)
	//	;
	
	token_end+=oper_ad;
	*start = token_end;
	// Allocate and copy the token
	token_len = token_end - token_start;

	token = malloc(token_len + 1);
	if (!token)
		return (NULL);
	strncpy(token, str + token_start, token_len);
	token[token_len] = '\0';
	return (token);
}


/*
have to fix command
cat<system.log>rep.txt
*/


// Main split function
/*
	EDGE CASES
	a\"b\"c\'d\'e				
	\"Mamman\'echo\'Papa\" 		
	\"%USER\"and\’$USER\’		
*/
t_arr 	*custom_split(const char *str, t_shell * shell)
{
	int		pos;
	int		token_index;
	t_arr	*result;

	
	if (!str)
		return NULL;
	result = malloc(sizeof(t_arr));
	if (!result)
		perror("Malloc");
	result->len = count_arg(str, shell); //have to implemente the <quote> if " or ' not closed
	result->arr = malloc(sizeof(char *) * (result->len));
	if (!result->arr)
	{
		free(result);
		perror("Malloc");
	}
	pos = 0;
	token_index = 0;
	while (token_index < result->len)
	{
		result->arr[token_index] = extract_arg(str, &pos, shell); //, &arr_token[token_index]);
		if (!result->arr[token_index])
		{
			for (int i = 0; i < token_index; i++)
				free(result->arr[i]);
			free(result->arr);
			free(result);
			perror("Erreur d'allocation pour les tokens");
		}
		printf("str %d:\t%s\n",token_index, (char *)result->arr[token_index]); //debug_print
		token_index++;
	}
	return result;
}

#include "mini.h"

// display subtoken
void print_all_parts(t_shell *shell)
{
	int n = 0;
	t_subtoken_conainter *container_parts;
	t_subtoken *sub_container_parts;
	
	t_token *token;
	while(n < shell->n_tokens)
	{
		token = &shell->tokens[n];
		if (token->type != TOKEN_CMD)
		{	
			printf("%s\n", token->value);
			n++;
			continue;
		}		
		int idx_parts = 0;
		int idx_subparts;

		char *types[] ={"no quote", "single quote", "double quote"};
		while(idx_parts<token->n_parts)
		{
			container_parts = &token->cmd_args_parts[idx_parts];
			idx_subparts = 0;
			while (idx_subparts<container_parts->n_parts)
			{
				sub_container_parts = &container_parts->parts[idx_subparts];
				printf("val {%.*s} \t type {%s} \t", sub_container_parts->len,sub_container_parts->p, types[sub_container_parts->type]);
				idx_subparts++;
			}
			printf("\n");
			idx_parts++;
		}
		n++;
	}
}

// Print dictionary-like array in the form key=value
void print_dic(t_arr *dic)
{
	int		i;
	char	**pair;

	i = 0;
	while (i < dic->len)
	{
		pair = (char **)dic->arr[i];
		printf("%s\t%p\n", pair[0], (void *)pair[1]);
		i++;
	}
}

void printStringArray(const char *cmd, const char *arr[]) {
    printf("%s: ", cmd);
    for (int i = 0; arr[i]!=NULL ; i++) {
        if (arr[i] != NULL) {
            printf("%s\t", arr[i]);
        }
    }
    printf("\n");
}

#include "mini.h"

void ft_free(void **thing)
{
    if (!*thing)
        return;
    free(*thing);
    *thing = NULL;
}

#include "mini.h"

void add_pid_env(t_shell *shell, int fd)
{
    pid_t received_pid;
    char s[20]; //PID= + sizeof(pid_t) =
    if (read(fd, s, 20) > 0)
        perror("add_pid_func");   
    ft_itoa_inplace(&s[4], (int) received_pid);
    replace_or_add(&shell->env,"PID=", (const char *)s);
}

void send_pid(int fd, int pid)
{
    write(fd, "PID=", sizeof("PID="));
    write(fd, &pid, sizeof(pid));  // Send child's PID to child
}


int start_cmd(t_shell *shell, int *prev_pipe, int *curr_pipe, t_list *curr_cmd)
{

    if (shell->fd_in == -1)
        shell->fd_in = STDIN_FILENO;
    int fd_pid[2];
    if (pipe(fd_pid) == -1)
        perror("fd_pid");
    int pid;
    pid = fork();
    if (pid < 0)
        perror("Forks");
    
    if (pid == 0)
    {
        add_pid_env(shell,fd_pid[0]);
        dup2(shell->fd_in, STDIN_FILENO);
        close(shell->fd_in);
        dup2(curr_pipe[1], STDOUT_FILENO);
        close(curr_pipe[0]);
        close(curr_pipe[1]);
        close(fd_pid[0]);
        close(fd_pid[1]);
        execute(shell,curr_cmd->content);
        exit(1);
    }

    if (shell->fd_in != STDIN_FILENO)
            close(shell->fd_in);
    send_pid(fd_pid[1],pid);
    close(curr_pipe[1]);
    close(fd_pid[0]);
    close(fd_pid[1]);
    prev_pipe[0] = curr_pipe[0];
    prev_pipe[1] = curr_pipe[1];
    curr_cmd = curr_cmd->next;
  
    return pid;
}

int end_cmd(t_shell *shell,int *prev_pipe, t_list *curr_cmd)
{
    (void) curr_cmd;
    if (shell->fd_out == -1)
        shell->fd_out = STDOUT_FILENO;
    int fd_pid[2];
    if (pipe(fd_pid) == -1)
        perror("fd_pid");

    int pid;
    pid = fork();
    if (pid < 0)
        perror("Forks");
    if (pid == 0)
    {
        add_pid_env(shell,fd_pid[0]);
        close(fd_pid[0]);
        close(fd_pid[1]);
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    
        dup2(shell->fd_out, STDOUT_FILENO);
        close(shell->fd_out);
        // Execute
        exit(1);
    }
    send_pid(fd_pid[1],pid);
    close(fd_pid[0]);
    close(fd_pid[1]);
    close(prev_pipe[0]);
    close(prev_pipe[1]);
    if (shell->fd_out != STDOUT_FILENO)
        close(shell->fd_out);

    return pid;
}


void one_command(t_shell *shell)
{ 
    if (shell->fd_in == -1)
        shell->fd_in = STDIN_FILENO;
    if (shell->fd_out == -1)
        shell->fd_out = STDOUT_FILENO;
    int fd[2];
    int fd_pid[2];

    if (pipe(fd) == -1 || pipe(fd_pid) == -1) {
        perror("pipe failed");
    }
    

    int pid = fork();    
    if (pid < 0)
    {
        perror("fork");
        return;
    }
    
    if (pid == 0)
    {
        int d; //debug
        scanf("%d", &d); // debug
        
        close(fd[1]);
        close(fd_pid[0]);  
        add_pid_env(shell,fd_pid[0]);
        close(fd[0]);
        close(fd_pid[0]);

        dup2(shell->fd_in, STDIN_FILENO);
        close(shell->fd_in);
        dup2(shell->fd_out, STDOUT_FILENO);
        close(shell->fd_out);
        execute(shell, shell->cmd_head->content);
        exit(1);
    }
    else
    close(fd[0]);  // Close read end
    close(fd_pid[0]);
    send_pid(fd_pid[1], pid);
    close(fd[1]);  // Close write end
    close(fd_pid[1]);

    waitpid(pid,NULL,0);
}

void launch_process(t_shell *shell)
{
    int i;
    int *pid;
    int prev_pipe[2] = {-1,-1};
    int curr_pipe[2];
    int fd_pid[2];
    t_list *curr_cmd = shell->cmd_head;

    if (shell->n_cmd == 1)
    {    
        one_command(shell);
        return ;
    }

    pid = malloc(sizeof(int)*shell->n_cmd);    
    if (!pid)
        return;
    i = 0;
    if(pipe(curr_pipe) < 0)
        perror("pipe");
    pid[i++] = start_cmd(shell, prev_pipe,curr_pipe,curr_cmd);
    while(curr_cmd->next != NULL)
    {
        if (pipe(fd_pid) == -1)
            perror("fd_pid");
        pid[i] = fork();
        if (pid[i] < 0)
            perror("Forks");
        if (pid[i] == 0)
        {
            add_pid_env(shell,fd_pid[0]);
            dup2(prev_pipe[0], STDIN_FILENO);
            close(prev_pipe[0]);
            close(prev_pipe[1]);
            close(fd_pid[0]);
            close(fd_pid[1]);


            dup2(curr_pipe[1], STDOUT_FILENO);
            close(curr_pipe[0]);
            close(curr_pipe[1]);
            // execute
            exit(1);
        }
        else
        {
            send_pid(fd_pid[1], (int) pid[i]);
            close(fd_pid[0]);
            close(fd_pid[1]);

            close(prev_pipe[0]);
            close(prev_pipe[1]);
            prev_pipe[0] = curr_pipe[0];
            prev_pipe[1] = curr_pipe[1];
            if(pipe(curr_pipe) == -1)
                perror("pipe"); //ERROR
        }
        curr_cmd = curr_cmd->next;
        i++;
    }
    pid[i++] = end_cmd(shell, prev_pipe,curr_cmd);
    while(i--)
        waitpid(pid[i], NULL, 0);
    free(pid);
}


static int count_args_cmd(t_shell *shell, int i)
{
	int n_args = 0;
	char **arr = (char **)shell->parsed_args->arr;
	int len = shell->parsed_args->len;
	
	int idx_oper;
	print_dic(shell->oper);
	while (1)
	{
		if (i==len)
			break;
		if (arr[i] != NULL)
		{
			printf("arg%d %s\n", i, arr[i]);
			idx_oper = is_in_t_arr_str(shell->oper, arr[i]);
			if (idx_oper != -1)
				return n_args;
			n_args++;
		}
		i++;
	}
	return n_args;
}

void subtoken_of_cmd(t_subtoken_conainter *container, char *arg)
{
	t_subtoken *parts;
	char *head = arg;
	int idx_tail;
	int n_parts = container->n_parts;
	container->parts = malloc(sizeof(t_subtoken)*n_parts);
	parts = container->parts;
	if (!parts)
		return;

	int i = 0;
	int idx = 0;
	while(head[idx])
	{
		if (head[idx] == '\'' && escape_check(head,idx))
		{	
			idx++;
			parts[i].type = QUOTE_SINGLE;
			idx_tail = find_c_nonescaped(&head[idx],"\'", 1);
		}
		else if (head[idx] == '\"' && escape_check(head,idx))
		{	
			idx++;
			parts[i].type = QUOTE_DOUBLE;
			idx_tail = find_c_nonescaped(&head[idx],"\"", 1);
		}
		else
		{	
			parts[i].type = QUOTE_NONE;
			idx_tail = find_c_nonescaped(&head[idx],"\"\'",2);
		}
		parts[i].len = idx_tail;
		parts[i].p = (char *)&head[idx];
		//printf("%.*s\n", idx_tail, &head[idx]);
		idx+= idx_tail+(parts[i].type != QUOTE_NONE);
		//if (parts[i].type != QUOTE_NONE)
		//	head+=2;
		i++;
	}
}



int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
	t_subtoken_conainter *arr_container;
	t_arr *arr_arg = shell->parsed_args;
	char *curr_arg;
	int idx_container = 0;
	cmd_token->cmd_args_parts = malloc(sizeof(t_subtoken_conainter *)*len);
	arr_container = cmd_token->cmd_args_parts;
	if (!arr_container)
		return -1;

	while(idx_container<len)
	{
		curr_arg = arr_arg->arr[idx];
		if (curr_arg != NULL)
		{
			arr_container[idx_container].n_parts = count_subtokens(curr_arg);
			subtoken_of_cmd(&arr_container[idx_container++], curr_arg);
		}
		idx++;
	}
	cmd_token->n_parts = len;
	return idx-1;
}


static void add_cmd(t_shell *shell, t_token *token)
{
	t_list *tmp;
 	tmp = malloc(sizeof(t_list));
	if (!tmp)
			return; // ERROR
	
	
	if (!shell->cmd_head)
	{	
		shell->cmd_head = tmp;
		shell->cmd_tail = tmp;
	}
	else
	{
		shell->cmd_tail->next = tmp;
		shell->cmd_tail = tmp;
	}
	tmp->content = (void *)token;
	tmp->next = NULL;
}


void attribute_token_type(t_shell *shell)
{
 	int t_arr_index;
    int i = 0;
	int idx_token = 0;
	void **arr = shell->parsed_args->arr;
	t_token *token;
	
	shell->n_tokens = count_tokens(shell);
	if (shell->n_tokens != 0)
	{
		shell->tokens = malloc(sizeof(t_token)*shell->n_tokens);
		if (!shell->tokens)
			perror("Erreur d'allocation pour les tokens");
	}
	while(idx_token < shell->n_tokens)
	{
		if (arr[i] != NULL)
		{
			token = &shell->tokens[idx_token];
			token->type = TOKEN_WORD;
			token->value = arr[i];
			
			//OPERATOR //les <> << >> sont deja gere par count_tokens, faudrait subdiviser (pour le bonus) les le parse pour subdiviser les tokens
			t_arr_index = is_in_t_arr_dic_str(shell->oper, arr[i]);
			if (t_arr_index != -1)
				token->type = TOKEN_OPER;
			//BCMD 
			if (token->type == TOKEN_WORD)
			{
				t_arr_index = is_in_t_arr_dic_str(shell->bcmd, arr[i]);
				if (t_arr_index != -1)
					token->type = TOKEN_BCMD;
				else
					token->type = TOKEN_CMD;
				i = attribute_cmd_subtokens(shell,token, i, count_args_cmd(shell,i));
			}
			if (token->type != TOKEN_OPER)
			{	
				add_cmd(shell,token);
				shell->n_cmd++;
			}
			i++;
		}
		idx_token++;
	}
}


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
	const char *arg = "ls -l | grep \".c\"";//"echo<system.log"; //"\"so \\\"hima\\\"ma\\\" bru\\\"";//"ls -la";
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
	//char **exp_cmd = expand_cmd(shell->tokens, shell->env);
	//printStringArray("cmd: ", (const char **)exp_cmd);
	shell->pids = malloc(sizeof(pid_t)*shell->n_cmd);
	if (!shell->pids)
		perror("MALLOC pids");

	//execv(find_command_path("ls", shell->env), (char *[]){"ls", NULL});	
	//test execute add path pid
	//replace_or_add(&shell->env,"P=","PID=4242");
	//execute(shell,shell->cmd_head->content);
	
	launch_process(shell);
	
	printf("\nlast line\n");
    return (0);
}
	
#include "mini.h"

/*

    FOR ALL HANDLER CAST t_shell

*/

int handle_heredoc(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling HEREDOC (<<) at token %d\n", token_idx);
    // TODO: Implement heredoc logic
    return (0);
}

int handle_append(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling APPEND (>>) at token %d\n", token_idx);
    // TODO: Implement append redirection logic
    return (0);
}

int handle_and(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling AND (&&) at token %d\n", token_idx);
    // TODO: Implement logical AND logic
    return (0);
}

int handle_or(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling OR (||) at token %d\n", token_idx);
    // TODO: Implement logical OR logic
    return (0);
}

int handle_pipe(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling PIPE (|) at token %d\n", token_idx);
    // TODO: Implement pipe logic
    return (0);
}

int handle_redirect_in(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling REDIRECT_IN (<) at token %d\n", token_idx);
    // TODO: Implement input redirection logic
    return (0);
}

int handle_redirect_out(void *shell, int token_idx)
{
    (void) shell;
    printf("Handling REDIRECT_OUT (>) at token %d\n", token_idx);
    // TODO: Implement output redirection logic
    return (0);
}


void handle_heredoc(t_shell *shell, int i)
{
  
    // Close previous fd_in to avoid leaks
    if (shell->fd_in != -1 && shell->fd_in != STDIN_FILENO)
        close(shell->fd_in);
      int hd_pipe[2];
    if (pipe(hd_pipe) < 0) {
        perror("pipe");
        return;
    }

    // Check if delimiter is quoted (use your subtoken logic)
    // TRAVAIL: IL FAUT EXPAND !
    char *delimiter =shell->parsed_args->arr[i+1];

    // Read input until delimiter
    char *line;
    while ((line = readline("> "))) { // Requires readline.h
        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        // If not quoted, expand $variables (implement later with your subtoken logic)

        // Write line + newline to pipe
        write(hd_pipe[1], line, strlen(line));
        write(hd_pipe[1], "\n", 1);
        free(line);
    }

    close(hd_pipe[1]); // Close write end
    shell->fd_in = hd_pipe[0]; // Set read end as input
}

// "<<",">>","&&","||","|","<",">"
//   0    1   2     3  	4   5   6
void file_access_redirection(t_shell *shell, int t_arr_index, int i)
{
    void **arr = shell->parsed_args->arr;
	if (i+1 >= shell->parsed_args->len)
		perror("Argument manquant pour l'opérateur"); // ERROR
	if (t_arr_index == 5)
	{
		if (shell->fd_in != -1) //<5 
		{
			shell->fd_in = open(arr[i+1], O_RDONLY);
			if (!shell->fd_in)
			 	perror("Erreur lors de l'ouverture en lecture"); // ERROR NOT OPENING;
		}
		else
		{
			if (access(arr[i+1], O_RDONLY) < 0)
				perror("ERROR ACCESS"); // ERROR NOT OPENING;
		}
		return;
	}
	if (t_arr_index == 0 && shell->fd_out != -1) //<< //HEREDOC
	{
		handle_heredoc(shell,i);
        return;
	}

	if (shell->fd_out != -1) // 1>> 6>  
	{
		if (t_arr_index == 1) 
		{
			shell->fd_out = open(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
			if (!shell->fd_out)
				perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
		}
		else if (t_arr_index == 6)
		{
			shell->fd_out = open(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC , 0644);
			if (!shell->fd_out)
				perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
		}
		return;
	}
	if (t_arr_index == 6)
	{
		if (access(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
	}
}

#include "mini.h"

// Helper function to get PATH from environment
char	*get_value_env(t_list *env, char *value, int len)
{
	t_list	*temp;
	temp = env;
	while (1)
	{
		if (strncmp(temp->content, value, len) == 0 && *(char* )(temp->content+len) == '=')
			return (temp->content + len +1); // Skip "value="
		temp = temp->next;
		if (temp == env)
			return (NULL);
	}
	return (NULL);
}

// Helper function to join path and command
static char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = strlen(dir);
	cmd_len = strlen(cmd);
	int i, j;
	full_path = malloc(dir_len + cmd_len + 2); // +2 for '/' and '\0'
	if (!full_path)
		return (NULL);
	// Copy directory
	i = 0;
	while (i < dir_len)
	{
		full_path[i] = dir[i];
		i++;
	}
	// Add separator
	full_path[i++] = '/';
	// Copy command
	j = 0;
	while (j < cmd_len)
	{
		full_path[i + j] = cmd[j];
		j++;
	}
	full_path[i + j] = '\0';
	return (full_path);
}

// Main function to find command path
char	*find_command_path(char *cmd, t_list *env)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*full_path;

	int i, start, len;
	// If command contains '/', it's already a path
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}
	// Get PATH envirnment variable
	path_env = get_value_env(env, "PATH", 4);
	if (!path_env)
		return (NULL);
	// Make a copy of PATH to work with
	len = strlen(path_env);
	path_copy = malloc(len + 1);
	if (!path_copy)
		return (NULL);
	strcpy(path_copy, path_env);
	// Search through each directory in PATH
	start = 0;
	i = 0;
	while (i <= len)
	{
		if (path_copy[i] == ':' || path_copy[i] == '\0')
		{
			path_copy[i] = '\0'; // Null-terminate current directory
			dir = path_copy + start;
			// Skip empty directories
			if (*dir != '\0')
			{
				full_path = join_path(dir, cmd);
				if (full_path && access(full_path, F_OK | X_OK) == 0)
				{
					free(path_copy);
					return (full_path);
				}
				if (full_path)
					free(full_path);
			}
			start = i + 1;
		}
		i++;
	}
	free(path_copy);
	return (NULL);
}

int count_exp_len(t_subtoken *b,int *k)
{
	int var_len = 0;
	if (isalpha(b->p[*k + 1]) || b->p[*k + 1] == '_') {
        var_len = 1;
        while (*k + 1 + var_len < b->len &&
               (isalnum(b->p[*k + 1 + var_len]) || b->p[*k + 1 + var_len] == '_')) {
            var_len++;
        }
	}
	return var_len;
}

void expand_variable(t_subtoken *b, int *k, t_list **curr, int *count, t_list *env)
{
    int var_len;
	var_len=count_exp_len(b,k);
	if (var_len>0)
	{
		char *value = get_value_env(env , (char *)&b->p[(*k)+1], var_len);
        push_lst(curr,ft_strdup_count (value,count));
		*k += var_len;
	}
}

void expand_str(t_subtoken *b, t_list *env, int *count, t_list **curr)
{
	int k = 0;
	while(k<b->len)
	{
		if (k < b->len && b->p[k] == '$') 
		{
			if (k + 1 == b->len || b->p[k + 1] == ' ') 
				push_lst(curr, ft_strdup_count("$", count));
			else if (b->p[k + 1] == '$')
			{
				push_lst(curr,strdup(get_value_env(env,"PID",3)));
				k++;
			}
			else
				expand_variable(b, &k, curr, count,env); // Handles variable case	
		}
		else
			(*count)++;
		k++;
	}
}

char *build_expansion(t_subtoken_conainter *a,int count, t_list **add_head)
{
	t_list *head = *add_head;
	char *new = malloc(count+1);
	if (!new)
		perror("MALLOC build_expansion");
	int i = 0;	
	int j = 0;
	int k;
	t_subtoken *b;
	t_list *tmp;

	while(j<a->n_parts) // 
	{
		b = &a->parts[j];
		if (b->type == QUOTE_SINGLE) 	//no expansion
		{
			strncpy(&new[i],b->p,b->len);
			i+=b->len;
		}
		else							//expansion
		{
			k = 0;
			while(k<b->len)
			{
				if (b->p[k] == '$')
				{
					strcpy(&new[i],head->content);
					i+=strlen(head->content);
					tmp = head;
					head = head->next;
					free(tmp->content);
					free(tmp);
					if (k+1<b->len && b->p[k+1] == '$')
						k++;
					else
						k+=count_exp_len(b,&k);
				}
				else
					new[i++] = b->p[k];
				k++;
			}
		}	
		j++;
	}
	new[i] = 0;
	return new;
}

char *expand_container(t_subtoken_conainter *a, t_list **head, t_list *env)
{
	t_list *curr = *head;
	int j = 0;
	t_subtoken *b;
	int count = 0;
	//char *arr_str = malloc(sizeof(char *)*a->n_parts);
	while(j<a->n_parts) // 
	{
		b = &a->parts[j];
		if (b->type == QUOTE_SINGLE) 	//no expansion
			count+=b->len;
		else							//expansion
			expand_str(b,env,&count,&curr);
		//if (curr && (curr)->content)
		//	printf("%s\n", (char *)(curr)->content);
		j++;
	}
	return build_expansion(a,count,&((*head)->next));
}


char **expand_cmd(t_token *token, t_list *env)
{
	int i;
	t_subtoken_conainter *a;
	t_list *head = ft_lstnew(NULL);
	char **res = malloc(sizeof(char *)*(token->n_parts)); //omits first
	if (!res)
		perror("MALLOC expand_cmd");


	// input "hello"a 'mom' 
	// {"hello"a}, {mom} container
	// {hello,a}, {mom} subtoken
	// {h,e,l,l,o} char * 
	i = 0;
	while(i<token->n_parts) // container
	{
		a = &token->cmd_args_parts[i];
		res[i] = expand_container(a,&head,env); 
		//printf("%s\n", res[i]);
		i++;
	}
	res[i] = NULL;
	return res;
}



void execute(t_shell *shell, t_token *cmd)
{
	char **args = expand_cmd(cmd,shell->env);
	//char **env = linked_to_array_string(shell->env);
	if (!args)
		perror("malloc res and env execute()");
	execv(find_command_path(cmd->value,shell->env), (char **const) args);
}


char *ft_strdup_count(const char *s, int *count)
{
    size_t len;
    char *dup;

    if (!s || !count) // Check for NULL inputs
        return (NULL);

    len = strlen(s);

    dup = (char *)malloc(len + 1); // Allocate for string + null terminator
    if (!dup)
        return (NULL);
    strncpy(dup,s,len);
    (*count)+=len; // Increment the counter
    return (dup);
}

//void ft_swap(void *a, void *b)
//{
//    void *tp;
//    tp = a;
//    b = a;
//    b = tp;
//}

char *ft_itoa_inplace(char *s, int n)
{
    char *start = s;
    char *ptr;
    int digits = 0;
    int temp;

    if (!s)
        return NULL;

    // Handle zero
    if (n == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return s;
    }

    // Handle negative numbers
    if (n < 0)
    {
        n = -n;
        *s++ = '-'; // Write sign directly
    }

    // Count digits and move to end position
    temp = n;
    while (temp > 0)
    {
        digits++;
        temp /= 10;
    }
    ptr = s + digits - 1; // Last digit position

    // Write digits in reverse order
    while (n > 0)
    {
        *ptr-- = (n % 10) + '0'; // Write digit
        n /= 10;
    }

    // Null-terminate
    *(s + digits) = '\0';

    return start;
}


#include "mini.h"

//array of string
size_t t_arrlen(void **arr)
{
    size_t len;

    if (!arr)
        return (0);
    
    len = 0;
    while (arr[len])
        len++;
    
    return (len);
}

/*	
	return (-1) not found
	return (%d != -1) idx of the one found in the array bcmd->arr
*/  
int is_in_t_arr_str(t_arr *arr, const char *arg)
{
    int i = 0;
    char *key;
    while (i < arr->len)
    {
        key = (char *)((t_dic *)arr->arr[i])->key;
        if (strcmp(key, arg) == 0)
            return (i);
        i++;
    }
    return (-1);
}

/*	
	For t_arr containing t_dic entries - searches by key
	return (-1) not found
	return (%d != -1) idx of the one found in the array
*/  
int is_in_t_arr_dic_str(t_arr *arr, const char *arg)
{
    int i = 0;
    t_dic *dic;
    int len_key;
    int len_arg;
    
    if (!arr || !arg)
        return (-1);
    
    len_arg = 1 + (arg[1]!= 0);
    while (i < arr->len)
    {
        dic = (t_dic *)arr->arr[i];
        char *str = dic->key;
        (void)str;
        len_key = strlen(dic->key);
        if (len_key<=len_arg)
        {
            if (dic && dic->key && strncmp((char *)dic->key, arg, len_key) == 0)
                return (i);
        }
        i++;
    }
    return (-1);
}

// build the dynamic array of the builtins cmd
void build_t_arr_str(t_arr **dst, char **arr_str, int len)
{
    *dst = malloc(sizeof(t_arr));
    if (!*dst)
        return;
    
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(char *) * len);
    if (!(*dst)->arr)
    {
        *dst = NULL;
        return;
    }
    
    int i = 0;
    while (i < len)
    {
        (*dst)->arr[i] = ft_strdup(arr_str[i]);
        if (!(*dst)->arr[i])
        {
            *dst = NULL;
            return;
        }
        i++;
    }
}

// build the dynamic array of t_dic entries
void build_t_arr_dic_str(t_arr **dst, char **keys, void **values, int len)
{
    *dst = malloc(sizeof(t_arr));
    t_dic *temp;
    if (!*dst)
        return;
    
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(t_dic *) * len);   // OK: array of pointers
    if (!(*dst)->arr)
        return;

    temp = malloc(sizeof(t_dic) * len);            // FIXED: struct-sized blocks
    if (!temp)
        return;
    
    int i = 0;
    while (i < len)
    {
        temp[i].key   = ft_strdup(keys[i]);         // duplicate key
        temp[i].value = values[i];                  // store handler ptr
        (*dst)->arr[i] = &temp[i];                  // point into temp[]
        if (!temp[i].key)
            return;
        printf("%s\t%p\n", (char *)temp[i].key, (int*)temp[i].value);
        i++;
    }
}

// initialise the builtins and operators
void init_all_t_arr(t_shell *shell)
{
	char *all_operators[] = {"<<",">>","&&","||","|","<",">"};
	char *all_builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    int (*operator_handlers[])(void *, int) = {
		NULL,     // "<<"
		NULL,      // ">>"
		NULL,         // "&&"
		NULL,          // "||"
		NULL,        // "|"
		NULL, // "<"
		NULL // ">"
	};
    int (*builtin_handlers[])(void *, int) = {
        ft_echo,
        ft_cd,
        ft_pwd,
        ft_export,
        ft_unset,
        ft_env,
        ft_exit,
        NULL
    };

	build_t_arr_dic_str(&shell->oper, all_operators, (void **)operator_handlers,sizeof(all_operators)/sizeof(char *));
    build_t_arr_dic_str(&shell->bcmd, all_builtins,  (void **)builtin_handlers,sizeof(all_builtins)/sizeof(char *));
}


#include "mini.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		perror("MALLOC in ft_lstnew");
	new->content = content;
	new->next = NULL;
	return (new);
}

//put at the end
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

//gives to the next
void	push_lst(t_list **tail, void *content)
{
	t_list *new;

	if (!*tail)
		return ;
	new = malloc(sizeof(t_list));
	if (!new)
		perror("MALLOC push_list");
	
	(*tail)->next = new;
	(*tail) = (*tail)->next; 
	new->content = content;
	new->next = NULL;
}


t_list	*set_linked_path(char **env)
{
	t_list	*head;
	t_list	*node;
	int		i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		node = ft_lstnew(strdup(env[i]));
		if (!node)
			return (NULL);
		ft_lstadd_back(&head, node);
		i++;
	}
	return (head);
}

static int count_linked(t_list *node)
{
	int count = 1;
	t_list *first = node;
	if (!node)
		return 0;
	node = node->next;
	while (node != first)
	{
		count++;
		node = node->next ; 
	}
	return count;
}

char **linked_to_array_string(t_list *node)
{
	t_list *first = node;
	int len = count_linked(node);
	char **arr = malloc(sizeof(char *)*(len+1));
	arr[len] = 0;
	int i = 0;

	while(i<len)
	{
		arr[i] = node->content;
		node = node->next;
		i++;
	}
	node = first;
	return arr;
}


void ft_lstadd_front(t_list **lst, void *content)
{
    t_list *new_node;

    if (!lst || !content)
        return;

    // Allocate new node
    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return; // Allocation failure

    // Duplicate content (assumes char *)
    new_node->content = strdup((char *)content);
    if (!new_node->content)
    {
        free(new_node);
        return; // Allocation failure
    }

    // Link new node to current head
    new_node->next = *lst;
    *lst = new_node; // Update head to new node
}

t_list *search_lst(t_list *lst, const char *target)
{
    size_t target_len;

    if (!lst || !target)
        return NULL;

    target_len = strlen(target);

    while (lst)
    {
        char *s  = (char *)lst->content;
        (void)s;
        if (lst->content && strncmp((char *)lst->content, target, target_len) == 0)
            return lst;
        lst = lst->next;
    }

    return NULL;
}



void replace_or_add(t_list **lst, const char *old, const char *new)
{
    t_list *node;

    if (!*lst || !old || !new)
        return;

    // Search for node matching old
    node = search_lst(*lst, old);
    if (node)
    {
        // Match found: free old content and replace
        free(node->content);
        node->content = strdup(new);
        if (!node->content)
        {
            // Handle strdup failure (optional: remove node or set to NULL)
            node->content = NULL;
        }
        return;
    }

    // No match: add new node at front
    ft_lstadd_front(lst, (void *)new);
}


/*
	trouve la premiere occurence de charactere
	str = Enrico et Noe sont beau
	needle = "o" (size 1)				return: "o et Noe sont beau"
	needle = "Nc" (size 2)				return: "co et Noe sont Beau"
	du coup c'est un strchr mais que si tu voulais chercher "N" et "c" 
	et voulais prendre le premier d'entre eux, ici elle te retourne naturellement le premier
	
	UTILISÉ dans 'token_attribute_parts_type' pour quand de UNQUOTED on passe a SINGLE/DOUBLE QUOTED mais on sais pas le quel
*/
int find_c_nonescaped(const char *str, char *needle, int size_needle)
{
	int c;
	int idx = 0;

	while (str[idx])
	{
		c = 0;
		while(c<size_needle && str[idx])
		{
			if (str[idx] == needle[c] && escape_check(str,idx))
				return idx;
			c++;
		}
		idx++;
	}
	return idx;
}

/*
	Ici on token les subtokens
*/
int count_subtokens(const char *str)
{
	bool in_single_quote;
	bool in_double_quote;
	bool in_no_quote;
	int i = 0;
	int count = 0;

	in_single_quote = 0;
	in_double_quote = 0;
	in_no_quote = 0;
	while(str[i])
	{
		if (str[i] == '\"' && !in_single_quote && escape_check(str,i))
		{
			in_no_quote = false;
			in_double_quote =!in_double_quote;
			if (in_double_quote)
				count++;
		}
		else if (str[i] == '\'' && !in_double_quote && escape_check(str,i))
		{
			in_no_quote = false;
			in_single_quote =!in_single_quote;
			if (in_single_quote)
				count++;
		}
		else if (!in_single_quote && !in_double_quote && !in_no_quote)
		{	
			count++;
			in_no_quote = true;
		}
		i++;
	}
	return count;
}

int count_tokens(t_shell *shell)
{
    int count = 1;
    int i = 0;
    void **arr = shell->parsed_args->arr;
    int len = shell->parsed_args->len;
    int idx_oper;
	if (len == 0)
		return 0;
	while(i<len)
	{
		while (i<len)
		{	
			idx_oper = is_in_t_arr_dic_str(shell->oper, arr[i]);
			if (idx_oper != -1)
			{
				if (idx_oper < 2 || idx_oper > 4)
				{
					file_access_redirection(shell, idx_oper, i);
					ft_free((void**)&shell->parsed_args->arr[i++]);
					if (i != len)
						ft_free((void**)&shell->parsed_args->arr[i]);	
				}
				else				
				{
					count++;
					i++;
					break;
				}
			}
			i++;
		}
	}
    return count+(idx_oper == -1);
}


