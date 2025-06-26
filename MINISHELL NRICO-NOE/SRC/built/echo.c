#include "../../include/minishell.h"

/*
int builtin_echo(char **args)
{
    int i = 1;

    if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
        i++;

    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (!args[1] || ft_strncmp(args[1], "-n", 2) != 0)
        printf("\n");
    return (0);
}*/
/*
char	*remove_quotes(const char *arg)
{
	int		i = 0, j = 0;
	char	quote = 0;
	char	*res = malloc(ft_strlen(arg) + 1);

	if (!res)
		return (NULL);

	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '"') && quote == 0)
			quote = arg[i];
		else if (arg[i] == quote)
			quote = 0;
		else
			res[j++] = arg[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}


int builtin_echo(char **args, t_minishell *shell)
{
	int i = 1;
	int newline = 1;
	char *processed;

	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		// Étape 1 : remplacer les variables comme $? ou $USER
		processed = replace_variables(args[i], shell);
		if (!processed)
			processed = ft_strdup("");

		// Étape 2 : enlever les quotes (tout en gardant le texte)
		char *final = remove_quotes(processed);
		free(processed);

		printf("%s", final);
		free(final);

		if (args[i + 1])
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");
    shell->exit_status = 0;
	return (0);
}*/


/*** Helpers pour quotes ***/
static int is_quote_char(char c)
{
    return (c == '"' || c == '\'');
}

static void update_quote_state(char c, char *qs)
{
    if (is_quote_char(c))
    {
        if (*qs == 0)
            *qs = c;
        else if (*qs == c)
            *qs = 0;
    }
}

/*** Helpers pour env ***/
static char *find_env_value(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

    

/*** Gestion $... ***/
// remplace $?, $VAR, touche perso $N
/*** Récupère la valeur associée à $… ***/


/*** Renvoie une chaîne allouée pour les variables “spéciales” ***/
/* - si key == "NOE"    → la touche perso
 * - si key == "ENRICO" → on ne fait rien (on renvoie NULL) 
 * - sinon             → NULL
 */
static char *get_special_var(const char *key)
{
    if (ft_strncmp(key, "NRICO", ft_strlen("NRICO") + 1) == 0)
        return NULL;
    if (ft_strncmp(key, "NOE", ft_strlen("NOE") + 1) == 0)
        return ft_strdup("le meilleur dev de la galaxie 🚀");
    return NULL;
}

/*** Récupère la valeur après $… ***/
static char *get_dollar_value(const char *arg, int *pos, t_minishell *sh)
{
    int  k = *pos + 1;
    char *key;
    char *val;

    if (arg[k] == '?')
    {
        val = ft_itoa(sh->exit_status);
        *pos = k + 1;
        return val;
    }

    /* on lit l’identifiant [A-Za-z0-9_] */
    int len = 0;
    while (ft_isalnum(arg[k + len]) || arg[k + len] == '_')
        len++;
    key = ft_substr(arg, k, len);

    /* d’abord dans l’env */
    val = find_env_value(sh->env, key);

    /* sinon, test “spécial” */
    if (!val)
        val = get_special_var(key);

    free(key);
    *pos = k + len;
    return val;
}

/*** Gestion $... ***/
static int handle_dollar(char *res, const char *arg, int *i, t_minishell *sh)
{
    char *val;
    int  nb = 0;

    val = get_dollar_value(arg, i, sh);
    if (val)
    {
        nb = ft_strlcpy(res, val, ft_strlen(val) + 1);
        free(val);
    }
    return nb;
}


/*** Remplacement des variables ***/
char *replace_variables(const char *arg, t_minishell *sh)
{
    int     i = 0, j = 0;
    int     in_sq = 0, in_dq = 0;
    char    *res = malloc(ft_strlen(arg) * 2 + 1);

    if (!res)
        return (NULL);
    while (arg[i])
    {
        if (arg[i] == '\'' && !in_dq)
            in_sq = !in_sq, i++;
        else if (arg[i] == '"' && !in_sq)
            in_dq = !in_dq, i++;
        else if (arg[i] == '$' && !in_sq)
            j += handle_dollar(&res[j], arg, &i, sh), i++;
        else
            res[j++] = arg[i++];
    }
    res[j] = '\0';
    return (res);
}

/*** Suppression des quotes ***/
char *remove_quotes(const char *arg)
{
    int     i = 0, j = 0;
    char    qs = 0;
    char    *res = malloc(ft_strlen(arg) + 1);

    if (!res)
        return (NULL);
    while (arg[i])
    {
        update_quote_state(arg[i], &qs);
        if (!is_quote_char(arg[i]))
            res[j++] = arg[i];
        i++;
    }
    res[j] = '\0';
    return (res);
}

/*** builtin_echo final ***/
int builtin_echo(char **args, t_minishell *sh)
{
    int     i = 1;
    int     nl = 1;
    char    *tmp;
    char    *out;

    if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
        nl = 0, i++;
    while (args[i])
    {
        tmp = replace_variables(args[i], sh);
        out = remove_quotes(tmp);
        free(tmp);

        printf("%s", out);
        free(out);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (nl)
        printf("\n");
    sh->exit_status = 0;
    return (0);
}



int builtin_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
