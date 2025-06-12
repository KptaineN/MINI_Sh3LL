#include "../include/minishell.h"


// parse la string "KEY=VALUE" en t_env
// Dans ton create_env (ou équivalent) :
t_env *create_env(char *env_str)
{
    t_env *node;
    char *equal;
    size_t key_len;

    node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    equal = ft_strchr(env_str, '=');
    if (!equal)
    {
        free(node);
        return NULL;
    }
    key_len = equal - env_str;
    node->key = malloc(key_len + 1);
    if (!node->key)
    {
        free(node);
        return NULL;
    }
    strncpy(node->key, env_str, key_len);
    node->key[key_len] = '\0';
    node->value = ft_strdup(equal + 1);
    node->next = NULL;
    return node;
}


void	init_minishell(t_minishell *shell, char **envp)
{
    shell->args = NULL; // Initialize command arguments to NULL
    shell->input = NULL; // Initialize user input to NULL
    shell->exit_status = 0; // Initialize exit status to 0
    shell->ast = NULL; // Initialize the AST to NULL
    shell->env = NULL; // Initialize the environment linked list to NULL
    if (!shell || !envp)
        return; // Check for NULL pointers
        
    shell->env = init_env(envp); // Initialize the environment linked list
    shell->args = NULL;
    shell->input = NULL;
    shell->exit_status = 0;
    shell->ast = NULL; // Initialize the AST to NULL

    // Initialize other components as needed
    // For example, set up signal handlers, initialize data structures, etc.
}

// construit toute la liste à partir de envp
t_env *init_env(char **envp)
{
    t_env *head = NULL, *tmp = NULL;
    int i = 0;
    while (envp[i])
    {
        t_env *node = create_env(envp[i]);
        if (!head)
            head = node;
        else
            tmp->next = node;
        tmp = node;
        i++;
    }
    return head;
}

int looping(t_minishell *shell)
{
    while (1)
    {
        shell->input = readline("minishell$ ");
        if (!shell->input)
        {
            ft_putendl_fd("exit", STDERR_FILENO);
            break;
        }
        if (ft_strlen(shell->input) > 0)
        {
            add_history(shell->input);
            parse_input(shell);      // À écrire : transforme en AST
            execute_command(shell);  // À écrire : exécute l’AST
        }
        free(shell->input);
        shell->input = NULL;
    }
    return 0;
}

/*
print_prompt : optionnel, tu peux mettre une couleur, ou afficher un état du shell (mais readline gère déjà un prompt simple).

readline("minishell$ ") : lit la ligne de l’utilisateur.

if (!shell->input) : détecte EOF (CTRL+D) ⇒ on sort proprement.

ft_strlen(shell->input) > 0 : n’ajoute à l’historique, ne parse et n’exécute que si ce n’est pas une ligne vide.

free : toujours, après chaque ligne lue, tu la libères pour éviter un leak à chaque boucle.

La boucle principale attend l’utilisateur, récupère sa ligne, vérifie EOF, historise, parse, exécute, libère.

Toujours free l’input, même si elle est vide ou n’a pas servi.

Organisation modulaire : tu peux ensuite faire évoluer parse_input et execute_command tranquillement.
*/

int start_init_minishell(t_minishell *shell, char **envp)
{
    if (!shell || !envp)
        return 0;

    init_minishell(shell, envp);
    looping(shell);
    // Here, you can add any additional initialization steps needed for your minishell

    // Additional initialization steps can be added here
    // For example, setting up signal handlers, initializing the AST, etc.

    return 1; // Return 1 on success
}
