
#include "echo.h"

/* ---------- Helpers identifiants ---------- */
static int is_name_start(int c) { return (c == '_' || ft_isalpha(c)); }
static int is_name_char (int c) { return (c == '_' || ft_isalnum(c)); }

/* ---------- PID helper ---------- */
char *ft_get_pid(void)
{
    pid_t pid = getpid();
    return ft_itoa((int)pid); // alloué -> à free par l'appelant
}

/* ---------- Specials persos ---------- */
static char *get_special_var(const char *key)
{
    if (ft_strncmp(key, "NRICO", 6) == 0) // +1 pas nécessaire si on compare sur len const
        return ft_strdup("le 2 eme meilleur dev de la galaxie 🚀");
    if (ft_strncmp(key, "NOE", 4) == 0)
        return ft_strdup("le meilleur dev de la galaxie 🚀");
    return NULL;
}

/* ---------- extract_key: lit [A-Za-z_][A-Za-z0-9_]* ---------- */
static char *extract_key(const char *arg, int start, int *len)
{
    int i = 0;

    // précondition: arg[start] est un is_name_start()
    while (is_name_char((unsigned char)arg[start + i]))
        i++;

    *len = i;
    // i ne peut pas être 0 si on a déjà testé is_name_start avant d'appeler
    return ft_substr(arg, start, i); // alloué
}

/* ---------- Dup env value (find_env_value renvoie pointeur interne) ---------- */
static char *env_value_dup(t_list *env, const char *key)
{
    char *ptr = find_env_value(env, key); // entry + keylen + 1, ou NULL
    if (!ptr) return NULL;
    return ft_strdup(ptr); // alloué
}

/* ---------- Special + Env ---------- */
static char *get_env_or_special_value(t_shell *shell, const char *key)
{
    char *val_env = env_value_dup(shell->env, key); // alloué si trouvé
    if (val_env)
        return val_env;
    return get_special_var(key); // alloué ou NULL
}

/*
 * Convention (alignée avec handle_dollar/process_dollar):
 * - retourne un buffer alloué (à copier puis free par handle_dollar) si EXPANSION
 * - retourne NULL si LITTÉRAL '$' (alors process_dollar écrira '$' et avancera *i de 1)
 * - *i est avancé de la quantité consommée
 */
char *get_dollar_value(const char *arg, int *i, t_shell *sh)
{
    int k = *i + 1; // on est sur '$' à arg[*i]

    // "$$" -> PID
    if (arg[k] == '$') {
        *i += 2;
        return ft_get_pid();
    }

    // "$?" -> code de retour
    if (arg[k] == '?') {
        *i += 2;
        return ft_itoa(sh->exit_status);
    }

    // "$" en fin de chaîne => littéral "$"
    if (arg[k] == '\0') {
        //*i += 1;         // on consomme juste '$'
        return NULL;     // process_dollar écrira '$'
    }

    // "$<digit>" -> vide (consume 2), compat pos params non gérés
    if (ft_isdigit((unsigned char)arg[k])) {
        *i += 2;
        return ft_strdup("");
    }

    // Si pas un début d'identifiant => "$" littéral (ne consomme QUE '$')
    if (!is_name_start((unsigned char)arg[k])) {
        //*i += 1;
        return NULL;     // '$' littéral
    }

    // Lire le nom de variable via extract_key()
    int   keylen = 0;
    char *key    = extract_key(arg, k, &keylen); // alloué
    char *val    = get_env_or_special_value(sh, key); // alloué ou NULL
    free(key);

    if (!val)
        val = ft_strdup(""); // var inconnue -> vide (comportement bash)

    *i += 1 + keylen; // on consomme '$' + nom
    return val;       // alloué -> sera free par handle_dollar après copie
}

/**
static char *find_env_value(t_list *env_list, const char *key)
{
    t_list *node = env_list;
    while (node)
    {
        t_list *current = (t_list *)node->content;
        if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
            return current->value;
        node = node->next;
    }
    return NULL;
}
char *find_env_value(t_list *env, const char *key)
{
    size_t keylen = ft_strlen(key);
    while (env)
    {
        char *entry = (char *)env->content;
        if (ft_strncmp(entry, key, keylen) == 0 && entry[keylen] == '=')
            return entry + keylen + 1;
        env = env->next;
    }
    return NULL;
}


static char *get_special_var(const char *key)
{
    if (ft_strncmp(key, "NRICO", ft_strlen("NRICO") + 1) == 0)
        return ft_strdup("le 2 eme meilleur dev de la galaxie 🚀");;
    if (ft_strncmp(key, "NOE", ft_strlen("NOE") + 1) == 0)
        return ft_strdup("le meilleur dev de la galaxie 🚀");
    return NULL;
}

static int is_valid_key_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

static char *extract_key(const char *arg, int start, int *len)
{
    int i = 0;
    while (is_valid_key_char(arg[start + i]))
        i++;
    *len = i;
    if (i == 0)
        return NULL;
    return ft_substr(arg, start, i);
}

static char *get_env_or_special_value(t_shell *shell, const char *key)
{
    char *val_env = find_env_value(shell->env, key);
    if (val_env)
        return ft_strdup(val_env);
    return get_special_var(key);
}

static int is_name_start(int c) { return (c == '_' || ft_isalpha(c)); }
static int is_name_char (int c) { return (c == '_' || ft_isalnum(c)); }

char *ft_get_pid(void)
{
    pid_t pid = getpid();
    // ft_itoa = ta lib; sinon écris un itoa
    return ft_itoa((int)pid);
}*/


/*
 * Règles:
 * - "$$"        -> PID (consume 2)
 * - "$?"        -> exit_status (consume 2)
 * - "$" seul
 *   ou "$" suivi d'un char NON [A-Za-z_0-9 ? $] -> LITTÉRAL "$" (consume 1, return NULL pour laisser process_dollar écrire '$')
 * - "$<name>"   -> valeur env (ou ""), consume (1 + len(name))
 * - "$<digit>"  -> comme bash pos parameters (non gérés ici) => "", consume 2
 *
 * Retourne:
 *   - char* alloué (à copier, puis free par handle_dollar)
 *   - NULL si on veut écrire '$' littéral (process_dollar s’en charge)
 *   - *i avancé correctement
 *char *get_dollar_value(const char *arg, int *i, t_shell *sh)
{
    int k = *i + 1; // on est sur '$' à arg[*i]

    // "$$" -> PID
    if (arg[k] == '$') {
        *i += 2;
        return ft_get_pid();
    }

    // "$?" -> exit_status
    if (arg[k] == '?') {
        *i += 2;
        return ft_itoa(sh->exit_status);
    }

    // "$" en fin de chaîne => littéral "$"
    if (arg[k] == '\0') {
        *i += 1;       // on consomme juste '$'
        return NULL;   // process_dollar écrira '$'
    }

    // "$<digit>" -> vide (consume 2)
    if (ft_isdigit((unsigned char)arg[k])) {
        *i += 2;
        return ft_strdup("");
    }

    // Si ce n'est pas un début de nom => "$" littéral (ne consomme QUE '$')
    if (!is_name_start((unsigned char)arg[k])) {
        *i += 1;
        return NULL;   // '$' littéral
    }

    // Lire le nom de variable
    int len = 0;
    while (is_name_char((unsigned char)arg[k + len]))
        len++;

    char *key = ft_substr(arg, k, len);
    char *val = get_env_or_special_value(sh, key);   // strdup(value) ou NULL
    free(key);

    if (!val)
        val = ft_strdup(""); // var inconnue -> vide

    *i += 1 + len; // on a consommé '$' + nom
    return val;
}*/

/*** Récupère la valeur après $… **
char *get_dollar_value(const char *arg, int *pos, t_shell *sh)
{
    int  k = *pos + 1;
    char *key;
    char *val;
    int len;

    if (arg[k] == '?')
    {
        val = ft_itoa(sh->exit_status);
        *pos = k + 1;
        return val;
    }
    key = extract_key(arg, k, &len);
    if (!key)
    {
        *pos = k;
        return NULL;
    }
    val = get_env_or_special_value(sh, key);
    free(key);
    *pos = k + len;
    return val;
}*/
