/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:16 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/03 04:46:19 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
int	looping(t_minishell *shell)
{
	while (1)
	{
		shell->input = readline("ᕕ( ᐛ )ᕗ minishell$ ");
		if (!shell->input)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (ft_strlen(shell->input) > 0)
		{
			add_history(shell->input);
			//parse_input(shell);     // À écrire : transforme en AST
			//execute_command(shell); // À écrire : exécute l’AST
		}
		free(shell->input);
		shell->input = NULL;
	}
	return (0);
}
int	looping(t_minishell *shell)
{
while (1)
{
	shell->input = readline("ᕕ( ᐛ )ᕗ minishell$");
	if (!shell->input)
		{
			write(1, "exit\n", 5);
			exit_shell(shell, shell->exit_status);
		}
	if (ft_strlen(shell->input) > 0)
	{
		add_history(shell->input);

		//ajouter le code de sortie dans l'input
		char *input_with_status = replace_exit_code(shell->input, shell->exit_status);
		if (!input_with_status)
		{
			free(shell->input);
			continue;
		}
		// BYPASS DU PARSING : AST fake minimal
		t_ast *fake = malloc(sizeof(t_ast));
		if (!fake)
			{
				free(shell->input);
				free(input_with_status);
				continue;
			}
		fake->type = NODE_COMMAND;
		fake->args = ft_split(shell->input, ' '); // naïf
		fake->filename = NULL;
		fake->left = NULL;
		fake->right = NULL;

		shell->ast = fake;

		if (fake->args)
				execute_command(shell);
		free_tab(fake->args);
		free(fake);
		free(input_with_status);
	
	}
	free(shell->input);
	shell->input = NULL;
}
return (0);
}*/
/*
char *read_user_input(void)
{
	char *input = readline("ᕕ( ᐛ )ᕗ minishell$");
	if (!input)
		write(1, "exit\n", 5);
	return input;
}

t_ast *create_fake_ast(const char *input)
{
	t_ast *node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->args = ft_split(input, ' ');
	node->filename = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}



void cleanup_after_exec(char *input, char *input_with_status, t_ast *ast)
{
	free_tab(ast->args);
	free(ast);
	free(input_with_status);
	free(input);
}


int	looping(t_minishell *shell)
{
	char	*input;
	char	*input_with_status;
	t_ast	*ast;

	while (1)
	{
		input = read_user_input();
		if (!input)
			exit_shell(shell, shell->exit_status);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue;
		}
		add_history(input);

		input_with_status = replace_exit_code(input, shell->exit_status);
		if (!input_with_status)
		{
			free(input);
			continue;
		}

		ast = create_fake_ast(input_with_status);
		if (!ast)
		{
			free(input);
			free(input_with_status);
			continue;
		}
		shell->ast = ast;
		if (ast->args)
			execute_command(shell);

		cleanup_after_exec(input, input_with_status, ast);
	}
	return (0);
}*/


/*
print_prompt : optionnel, tu peux mettre une couleur,
	ou afficher un état du shell (mais readline gère déjà un prompt simple).

readline("minishell$ ") : lit la ligne de l’utilisateur.

if (!shell->input) : détecte EOF (CTRL+D) ⇒ on sort proprement.

ft_strlen(shell->input) > 0 : n’ajoute à l’historique,
	ne parse et n’exécute que si ce n’est pas une ligne vide.

free : toujours, après chaque ligne lue,
	tu la libères pour éviter un leak à chaque boucle.

La boucle principale attend l’utilisateur, récupère sa ligne, vérifie EOF,
	historise, parse, exécute, libère.

Toujours free l’input, même si elle est vide ou n’a pas servi.

Organisation modulaire : tu peux ensuite faire évoluer parse_input et execute_command tranquillement.
*/

/*** 1) Lecture de l’input ***/
char *read_user_input(void)
{
    char *input = readline("ᕕ( ᐛ )ᕗ minishell$ ");
    if (!input)
        write(1, "exit\n", 5);
    return (input);
}

/*** 2) Injection de $? ***/
char *expand_status(char *input, t_minishell *sh)
{
    char *res = replace_exit_code(input, sh->exit_status);
    return (res);  // à free par l’appelant
}

/*** 3) Expansion des autres variables ***/
/* Cette fonction est supposée exister : replace_variables(const char*, t_minishell*) */

/*** 4) Création d’un AST factice ***/
t_ast *create_fake_ast(const char *input)
{
    t_ast *node = malloc(sizeof(*node));
    if (!node)
        return (NULL);
    node->type     = NODE_COMMAND;
    node->args     = ft_split(input, ' ');
    node->filename = NULL;
    node->left     = NULL;
    node->right    = NULL;
    return (node);
}

/*** 5) Nettoyage après exécution ***/
void cleanup_after_exec(char *input, char *expanded, t_ast *ast)
{
    free_tab(ast->args);
    free(ast);
    free(expanded);
    free(input);
}

int looping(t_minishell *shell)
{
    char  *input;
    char  *step1;
    char  *step2;
    t_ast *ast;

    while (1)
    {
        // 1) lecture
        input = read_user_input();
        if (!input)
            break;  // EOF (CTRL+D)

        if (*input == '\0')
        {
            free(input);
            continue;
        }
        add_history(input);

        // 2) remplacer $?
        step1 = expand_status(input, shell);
        if (!step1)
        {
            free(input);
            continue;
        }

        // 3) remplacer $VAR, $USER, $NOE…
        step2 = replace_variables(step1, shell);
        free(step1);
        if (!step2)
        {
            free(input);
            continue;
        }

		ast = create_fake_ast(step2);
		if (!ast)
		{
			free(step2);
			free(input);
			continue;
		}
		
		// ❶ on stocke l'AST dans le shell
		shell->ast = ast;
		
		// ❷ on exécute
		execute_command(shell);
		
		// ❸ on nettoie après exécution
		cleanup_after_exec(input, step2, ast);
		// (ici cleanup doit free(ast->args), free(ast), free(step2), free(input))
		
    }
    return (0);
}
