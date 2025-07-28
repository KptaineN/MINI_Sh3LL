/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-3-free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 13:19:11 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



void	free_args(char **args)
{
	int	i = 0;

	if (!args)
		return;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void ft_free_array(char **arr)
{
    int i = 0;
    if (!arr) return;
    while (arr[i]) free(arr[i++]);
    free(arr);
}

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void free_tab(char **tab)
{
	int i;

	if (!tab)
		return;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void free_t_arr(t_arr *array)
{
	if (!array)
		return;
	if (array->arr)
	{
		for (int i = 0; i < array->len; i++)
			free(array->arr[i]);
		free(array->arr);
	}
	free(array);
}

/*void free_tab(char **tab)
{
    int i = 0;
    while (tab && tab[i])
        free(tab[i++]);
    free(tab);
}*/

void free_tokens(t_shell *parser)
{
    if (!parser || !parser->tokens)
        return;

    for (int i = 0; i < parser->n_tokens; i++)
    {
        t_token *tok = &parser->tokens[i];

		if (tok->type == TOKEN_WORD)
		{
			if (tok->value)
				free(tok->value);
		}
        else if (tok->type == TOKEN_BCMD || tok->type == TOKEN_CMD)
        {
            if (tok->cmd_args_parts)
            {
                for (int j = 0; j < count_subtoken_args(tok->cmd_args_parts); j++)
                {
                    if (tok->cmd_args_parts[j].parts)
                        free(tok->cmd_args_parts[j].parts);
                }
                free(tok->cmd_args_parts);
            }

            // Si c'était un CMD, on aurait fait un strdup du chemin :
            if (tok->type == TOKEN_CMD && tok->value)
                free(tok->value);
        }
    }

    free(parser->tokens);
    parser->tokens = NULL;
    parser->n_tokens = 0;

	// Libère la liste chaînée de commandes
	t_list *tmp;
	while (parser->cmd_head)
	{
		tmp = parser->cmd_head->next;
		if (parser->cmd_head->content)
			free(parser->cmd_head->content);
		free(parser->cmd_head);
		parser->cmd_head = tmp;
	}
	parser->cmd_head = NULL;
	parser->cmd_tail = NULL;

    parser->n_cmd = 0;
}


/*
void	free_ast(t_ast *node)
{
	if (!node)
		return;

	// Libère récursivement les sous-arbres
	free_ast(node->left);
	free_ast(node->right);

	// Libère le tableau d'arguments (pour les commandes)
	free_args(node->args);

	// Libère le nom de fichier (pour les redirections)
	if (node->filename)
		free(node->filename);

	// Libère le nœud lui-même
	free(node);
}
*/
void	clean_exit(char **cmd_args, char *msg, int code)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	if (cmd_args)
		ft_free_split(cmd_args);
	exit(code);
}

 //* Libère toute la mémoire de la structure minishell.
void	free_env_list(t_list *env)
{
	t_list *tmp;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->content)
		{
			t_env *env_node = (t_env *)tmp->content;
			if (env_node->key)
				free(env_node->key);
			if (env_node->value)
				free(env_node->value);
			free(env_node);
		}
		free(tmp);
	}
}


void free_parser(t_shell *parser)
{
	if (!parser)
		return;
	/* free input string */
	if (parser->input)
		free(parser->input);
	/* free parsed arguments array */
	if (parser->parsed_args)
		free_t_arr(parser->parsed_args);
	/* free tokens and command list */
	free_tokens(parser);
	/* free environment variables list */
	if (parser->env)
		free_env_list(parser->env);
	/* free builtins and operators arrays */
	if (parser->bcmd)
		free_t_arr(parser->bcmd);
	if (parser->oper)
		free_t_arr(parser->oper);
	/* free child process IDs */
	if (parser->pids)
		free(parser->pids);
	/* free heredoc subtokens */
	if (parser->heredoc)
	{
		if (parser->heredoc->parts)
			free(parser->heredoc->parts);
		free(parser->heredoc);
	}
}

void free_minishell(t_minishell *shell)
{
	if (!shell)
		return;
	free_parser(&shell->parser);
	if (shell->args)
		ft_free_split(shell->args);
	free(shell);
}

// Fichier : exit_utils.c par exemple
void	exit_shell(t_minishell *shell, int exit_code)
{
	free_minishell(shell);
	rl_clear_history(); // nettoie readline
	exit(exit_code);
}

