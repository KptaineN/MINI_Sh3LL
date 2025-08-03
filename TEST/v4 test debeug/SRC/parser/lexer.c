/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:20:55 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 15:05:35 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
	Ici on attribue les sous‐types
	*array de pointeur de taille n_parts

void attribute_subtoken_type(t_token *token)
{
	const char *subtoken;
	int idx_tail;
	t_subtoken *parts;
	int n_parts = token->u.all_parts.n_parts;

	token->u.all_parts.parts = malloc(sizeof(t_subtoken) * n_parts);
	if (!token->u.all_parts.parts)
		return;

	subtoken = token->value;
	parts    = token->all_parts.parts;
	int i = 0;
	int idx = 0;
	while (subtoken[idx])
	{
		if (subtoken[idx] == '\'' && escape_check(subtoken, idx))
		{
			idx++;
			parts[i].type = QUOTE_SINGLE;
			idx_tail     = find_c_nonescaped(&subtoken[idx], "\'", 1);
		}
		else if (subtoken[idx] == '\"' && escape_check(subtoken, idx))
		{
			idx++;
			parts[i].type = QUOTE_DOUBLE;
			idx_tail     = find_c_nonescaped(&subtoken[idx], "\"", 1);
		}
		else
		{
			parts[i].type = QUOTE_NONE;
			idx_tail     = find_c_nonescaped(&subtoken[idx], "\"\'", 2);
		}
		parts[i].len = idx_tail + 1;
		parts[i].p   = (char *)&subtoken[idx];
		idx += idx_tail;
		i++;
	}
}*/
/*
static int count_args_cmd(t_shell *shell, int i)
{
	int n_args = 0;
	int curr;
	char *temp;
	char **arr = (char **)shell->parsed_args->arr;

	curr = i + 1;
	while (curr < shell->n_tokens
	   && is_in_t_arr_str(shell->oper, arr[curr]) == -1
	   && is_in_t_arr_str(shell->oper, arr[curr]) == -1)
	{
		temp = find_command_path(arr[curr], shell->env);
		if (temp)
		{
			free(temp);
			return n_args;
		}
		n_args++;
		curr++;
	}
	return n_args;
}*/


void add_cmd(t_shell *shell, t_token *token)
{
    t_list *tmp = malloc(sizeof(t_list));
    if (!tmp)
    {
        perror("Erreur malloc add_cmd");
        return;
    }

    tmp->content = (void *)token;
    tmp->next = NULL;

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
}

int count_args_cmd(t_shell *shell, int i)
{
    int n_args = 0;
    char **arr;
    int len;
    int idx_oper;

    if (!shell || !shell->parsed_args || !shell->parsed_args->arr)
        return 0;

    arr = (char **)shell->parsed_args->arr;
    len = shell->parsed_args->len;

    while (i < len && arr[i] != NULL)
    {
        printf("count_args_cmd: arr[%d] = \"%s\"\n", i, arr[i]);

        // Vérifie si on tombe sur un opérateur (|, <, >, etc.)
        idx_oper = is_in_t_arr_dic_str(shell->oper, arr[i]);
        if (idx_oper != -1)
        {
            // On s'arrête avant l'opérateur
            return n_args;
        }

        n_args++;
        i++;
    }

    if (n_args == 0)
    {
        printf("count_args_cmd: No valid arguments found.\n");
        return 1; // Par défaut, on considère 1 argument (au moins la commande elle-même)
    }
    return n_args;
}

/*void subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
    if (!container || !arg)
    {
        fprintf(stderr, "subtoken_of_cmd: paramètres NULL\n");
        return;
    }

    int n_parts = container->n_parts;
    if (n_parts <= 0)
    {
        fprintf(stderr, "subtoken_of_cmd: n_parts=%d invalide\n", n_parts);
        return;
    }

    t_subtoken *parts = container->parts;
    int i = 0;
    int idx = 0;
    int idx_tail = 0;
    int arg_len = ft_strlen(arg);

    printf("subtoken_of_cmd: processing \"%s\" (len=%d, n_parts=%d)\n", arg, arg_len, n_parts);

    while (idx < arg_len && i < n_parts)
    {
        if (arg[idx] == '\'' && escape_check(arg, idx))
        {
            int start = idx + 1;
            parts[i].type = QUOTE_SINGLE;
            idx_tail = find_c_nonescaped(&arg[start], "\'", 1);
            if (idx_tail < 0)
            {
                fprintf(stderr, "subtoken_of_cmd: quote simple non fermée\n");
                idx_tail = arg_len - start; // on prend le reste
            }
            parts[i].len = idx_tail;
            parts[i].p = ft_substr(arg, start, idx_tail);
            idx = start + idx_tail + 1;
        }
        else if (arg[idx] == '"' && escape_check(arg, idx))
        {
            int start = idx + 1;
            parts[i].type = QUOTE_DOUBLE;
            idx_tail = find_c_nonescaped(&arg[start], "\"", 1);
            if (idx_tail < 0)
            {
                fprintf(stderr, "subtoken_of_cmd: quote double non fermée\n");
                idx_tail = arg_len - start;
            }
            parts[i].len = idx_tail;
            parts[i].p = ft_substr(arg, start, idx_tail);
            idx = start + idx_tail + 1;
        }
        else
        {
            int start = idx;
            parts[i].type = QUOTE_NONE;
            idx_tail = find_c_nonescaped(&arg[start], "\"\'", 2);
            if (idx_tail < 0)
                idx_tail = arg_len - idx;
            parts[i].len = idx_tail;
            parts[i].p = ft_substr(arg, start, idx_tail);
            idx = start + idx_tail;
        }
        i++;
    }

    printf("subtoken_of_cmd: traité %d parties sur %d\n", i, n_parts);
}*/

/**
void subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
	if (!container || !arg)
        return;

	t_subtoken *parts = NULL;
	int n_parts = container->n_parts;
	if (n_parts <= 0)
        return;

	container->parts = malloc(sizeof(t_subtoken) * n_parts);
	if (!container->parts)
		return;

	char *head = arg;
	parts = container->parts;
	int idx_tail;
	int i   = 0;
	int idx = 0;
	while (head[idx] && i < n_parts)
	{
		if (head[idx] == '\'' && escape_check(head, idx))
		{
			head++;
			parts[i].type = QUOTE_SINGLE;
			idx_tail     = find_c_nonescaped(&head[idx], "\'", 1);
		}
		else if (head[idx] == '\"' && escape_check(head, idx))
		{
			head++;
			parts[i].type = QUOTE_DOUBLE;
			idx_tail     = find_c_nonescaped(&head[idx], "\"", 1);
		}
		else
		{
			parts[i].type = QUOTE_NONE;
			idx_tail     = find_c_nonescaped(&head[idx], "\"\'", 2);
		}
		parts[i].len = idx_tail;
		parts[i].p = (char *)&head[idx];
		//printf("%.*s\n", idx_tail, &head[idx]);
		idx+= idx_tail+(parts[i].type != QUOTE_NONE);
		//parts[i].len = idx_tail + 1;
		//parts[i].p   = head;
		//idx += idx_tail;
		i++;
	}
}
void subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
    if (!container || !arg)
        return;

    t_subtoken *parts = NULL;
    int n_parts = container->n_parts;
    if (n_parts <= 0)
        return;

    container->parts = malloc(sizeof(t_subtoken) * n_parts);
    if (!container->parts)
        return;

    parts = container->parts;
    int i = 0;
    int idx = 0;
    int idx_tail = 0;
    int arg_len = ft_strlen(arg);

    while (idx < arg_len && i < n_parts)
    {
        if (arg[idx] == '\'' && escape_check(arg, idx))
        {
            int start = idx + 1;
            parts[i].type = QUOTE_SINGLE;
            idx_tail = find_c_nonescaped(&arg[start], "\'", 1);
            if (idx_tail < 0) break; // Pas de quote fermante, on stoppe
            parts[i].len = idx_tail;
            parts[i].p = (char *)&arg[start];
            idx = start + idx_tail + 1; // saute la quote fermante
        }
        else if (arg[idx] == '\"' && escape_check(arg, idx))
        {
            int start = idx + 1;
            parts[i].type = QUOTE_DOUBLE;
            idx_tail = find_c_nonescaped(&arg[start], "\"", 1);
            if (idx_tail < 0) break; // Pas de quote fermante
            parts[i].len = idx_tail;
            parts[i].p = (char *)&arg[start];
            idx = start + idx_tail + 1; // saute la quote fermante
        }
        else
        {
            int start = idx;
            parts[i].type = QUOTE_NONE;
            idx_tail = find_c_nonescaped(&arg[start], "\"\'", 2);
            if (idx_tail < 0) idx_tail = arg_len - idx; // Jusqu'à la fin si rien trouvé
            parts[i].len = idx_tail;
            parts[i].p = (char *)&arg[start];
            idx = start + idx_tail;
        }
        i++;
    }
}


int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
	t_arr *arr_arg = shell->parsed_args;
	t_subtoken_container *containers;
	char *curr_arg;
	char *temp;
	int idx_container = 0;

	// allouer len+1 pour le marqueur de fin 
	containers = malloc(sizeof(*containers) * (len + 1));
	if (!containers)
		return -1;
	cmd_token->u.cmd_args_parts = containers;

	idx++;
	while (idx < len)
	{
		curr_arg = arr_arg->arr[idx];
		temp     = find_command_path(curr_arg, shell->env);

		if (temp
		 && is_in_t_arr_dic_str(shell->oper, curr_arg) == -1
		 && is_in_t_arr_str(shell->oper, curr_arg)     == -1)
		{
			free(temp);
			break;
		}

		containers[idx_container].n_parts = count_subtokens(curr_arg);
		subtoken_of_cmd(&containers[idx_container], curr_arg);

		idx_container++;
		idx++;
		free(temp);
	}

	// marqueur de fin 
	containers[idx_container].n_parts = 0;
	containers[idx_container].parts   = NULL;

	return idx;
}*/

void file_access_redirection(t_shell *shell, void **arr, int t_arr_index, int i)
{
	if (i + 1 >= shell->n_tokens)
		perror("Argument manquant pour l'opérateur");

	if (t_arr_index == 5)
	{
		if (shell->fd_in != -1)
		{
			shell->fd_in = open(arr[i + 1], O_RDONLY);
			if (shell->fd_in < 0)
				perror("Erreur lors de l'ouverture en lecture");
		}
		else if (access(arr[i + 1], O_RDONLY) < 0)
		{
			perror("ERROR ACCESS");
		}
		return;
	}

	// sortie 
	if (shell->fd_out != -1)
	{
		if (t_arr_index == 1)
		{
			shell->fd_out = open(arr[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (shell->fd_out < 0)
				perror("Erreur lors de l'ouverture en écriture (append)");
		}
		else if (t_arr_index == 6)
		{
			shell->fd_out = open(arr[i + 1], O_CREAT | O_RDWR, 0644);
			if (shell->fd_out < 0)
				perror("Erreur lors de l'ouverture en écriture (trunc)");
		}
		return;
	}

	if (t_arr_index == 1)
	{
		if (access(arr[i + 1], O_CREAT | O_RDWR | O_APPEND | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (append)");
	}
	else if (t_arr_index == 6)
	{
		if (access(arr[i + 1], O_CREAT | O_RDWR | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (trunc)");
	}
}
/*int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
    if (!shell || !cmd_token || !shell->parsed_args || !shell->parsed_args->arr)
    {
        fprintf(stderr, "attribute_cmd_subtokens: paramètres NULL\n");
        return idx + 1;
    }

    if (len <= 0)
    {
        fprintf(stderr, "attribute_cmd_subtokens: len=%d invalide\n", len);
        return idx + 1;
    }

    t_arr *arr_arg = shell->parsed_args;
    char **args = (char **)arr_arg->arr;
    t_subtoken_container *containers;
    int idx_container = 0;

    printf("attribute_cmd_subtokens: idx=%d, len=%d\n", idx, len);

    // Allocation sécurisée du tableau de containers
    containers = calloc(len + 1, sizeof(t_subtoken_container));
    if (!containers)
    {
        perror("attribute_cmd_subtokens: échec allocation containers");
        return idx + len;
    }
    cmd_token->cmd_args_parts = containers;

    // Traiter chaque argument
    while (idx_container < len && idx < arr_arg->len)
    {
        char *curr_arg = args[idx];
        if (!curr_arg)
        {
            fprintf(stderr, "attribute_cmd_subtokens: curr_arg NULL à l'index %d\n", idx);
            break;
        }

        printf("attribute_cmd_subtokens: processing arg[%d] = \"%s\"\n", idx, curr_arg);

        int n_parts = count_subtokens(curr_arg);
        containers[idx_container].n_parts = n_parts;

        if (n_parts > 0)
        {
            containers[idx_container].parts = malloc(sizeof(t_subtoken) * n_parts);
            if (!containers[idx_container].parts)
            {
                perror("attribute_cmd_subtokens: échec allocation parts");
                break;
            }
            subtoken_of_cmd(&containers[idx_container], curr_arg);
        }
        else
        {
            containers[idx_container].parts = NULL;
        }

        idx_container++;
        idx++;
    }

    // Marquer la fin
    if (idx_container < len)
    {
        containers[idx_container].n_parts = 0;
        containers[idx_container].parts = NULL;
    }

    return idx;
}*/

/**
int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
	t_subtoken_container *arr_containers;
	t_arr *arr_arg = shell->parsed_args;
	char *curr_arg;
	int idx_container = 0;

	// allocate len+1 for the end marker
	cmd_token->cmd_args_parts = malloc(sizeof(t_subtoken_container) * (len + 1));
	arr_containers = cmd_token->cmd_args_parts;
	if (!arr_containers)
		return -1;
	//cmd_token->cmd_args_parts = arr_containers;

	// fill containers[0..len-1]
	while (idx_container < len)
	{
		curr_arg = arr_arg->arr[idx];
		if (curr_arg)
		{
			arr_containers[idx_container].n_parts = count_subtokens(curr_arg);
			subtoken_of_cmd(&arr_containers[idx_container++], curr_arg);
		}
		idx++;
	}

	cmd_token->cmd_args_parts->n_parts = len;
	// end marker
	//containers[idx_container].n_parts = 0;
	//containers[idx_container].parts   = NULL;

	return idx + len;
}*/

/*void attribute_token_type(t_shell *shell)
{
    int i = 0;
    int idx_token = 0;
    int len;
    void **arr = shell->parsed_args->arr;

    if (!shell || !arr)
    {
        shell->n_tokens = 0;
        return;
    }

    // Nombre total de tokens (commandes + opérateurs)
    shell->n_tokens = count_tokens(shell, shell->parsed_args, shell->oper);
    if (shell->n_tokens <= 0)
        return;

    shell->tokens = calloc(shell->n_tokens, sizeof(t_token));
    if (!shell->tokens)
    {
        perror("Erreur d'allocation pour les tokens");
        exit(EXIT_FAILURE);
    }

    len = shell->parsed_args->len;
    while (i < len && idx_token < shell->n_tokens)
    {
        t_token *token = &shell->tokens[idx_token];
        token->value = arr[i];
        token->type = TOKEN_WORD;

        // Vérifier si l'élément actuel est un opérateur
        if (is_in_t_arr_dic_str(shell->oper, arr[i]) != -1)
        {
            token->type = TOKEN_OPER;
            i++;  // on avance juste d'un opérateur
        }
        else
        {
            // Vérifier si c'est un builtin
            if (is_in_t_arr_str(shell->bcmd, arr[i]) != -1)
                token->type = TOKEN_BCMD;
            else
                token->type = TOKEN_CMD;

            // Gestion des arguments pour cette commande
            int nb_args = count_args_cmd(shell, i);
            if (nb_args <= 0)
                nb_args = 1;

            int new_i = attribute_cmd_subtokens(shell, token, i, nb_args);
            if (new_i <= i)
            {
                printf("BUG: attribute_cmd_subtokens n'avance pas (%d -> %d), incrément manuel !\n", i, new_i);
                i++;
            }
            else
                i = new_i;
        }

        // Ajouter la commande dans la liste si ce n'est pas un opérateur
        if (token->type != TOKEN_OPER)
        {
            add_cmd(shell, token);
            shell->n_cmd++;
        }

        idx_token++;
    }
}*/




/*
void attribute_token_type(t_shell *shell)
{
	int t_arr_index;
	int i = 0;
	int idx_token = 0;
	void **arr = shell->parsed_args->arr;
	t_token *token;

	shell->n_tokens = count_tokens(shell, shell->parsed_args, shell->oper);
	if (shell->n_tokens != 0)
	{
		shell->tokens = malloc(sizeof(t_token) * shell->n_tokens);
		if (!shell->tokens)
			perror("Erreur d'allocation pour les tokens");
	}
	while (idx_token < shell->n_tokens)
	{
		if (arr[i] != NULL)
		{
			token = &shell->tokens[idx_token];
			token->type = TOKEN_WORD;
			token->value = arr[i];

			// operator
			t_arr_index = is_in_t_arr_dic_str(shell->oper, arr[i]);
			if (t_arr_index != -1)
				token->type = TOKEN_OPER;
			else
			{
				// === 2. Cherche BUILTIN (CORRIGÉ) ===
				t_arr_index = is_in_t_arr_str(shell->bcmd, arr[i]);
				if (t_arr_index != -1)
					token->type = TOKEN_BCMD;
				else
					token->type = TOKEN_CMD;

				// === 3. Gestion des arguments/subtokens ===
				int nb_args = count_args_cmd(shell, i);
				if (nb_args <= 0)
					nb_args = 1;

				int old_i = i;
				int new_i = attribute_cmd_subtokens(shell, token, i, nb_args);

				if (new_i <= old_i) {
					printf("BUG: attribute_cmd_subtokens n’avance pas (%d -> %d) — on avance à la main !\n", old_i, new_i);
					i = old_i + 1;
				} else {
					i = new_i;
				}
			}

			if (token->type != TOKEN_OPER)
			{
				add_cmd(shell, token);
				shell->n_cmd++;
			}
			i++;
			idx_token++;
		}
		else
		{
			i++;
		}
	}
}

void attribute_token_type(t_shell *shell)
{
	int    t_arr_index;
	int    i         = 0;
	int    idx_token = 0;
	void **arr       = shell->parsed_args->arr;
	t_token *token;
	//bool   c;

	shell->n_tokens = count_tokens(shell->parser);
	//shell->tokens   = malloc(sizeof(t_token) * shell->n_tokens);
	if (shell->n_tokens != 0)
	{
		shell->tokens = malloc(sizeof(t_token)*shell->n_tokens);
		if (!shell->tokens)
			perror("Erreur d'allocation pour les tokens");
	}
	while (idx_token < shell->n_tokens) //i < shell->n_tokens
	{
		//c     = false;
		token = &shell->tokens[idx_token];
		//token->idx   = idx_token;
		token->type  = TOKEN_WORD;
		token->value = arr[i];

		// OPERATOR ? 
		t_arr_index = is_in_t_arr_dic_str(shell->oper, arr[i]);
		if (t_arr_index != -1)
		{
			//c         = true;
			token->type = TOKEN_OPER;
			if (t_arr_index == 1 || t_arr_index == 5 || t_arr_index == 6)
				file_access_redirection(shell, arr, t_arr_index, i);
			// else << 
		}

		// BUILTIN ? 
		if (!c)
		{
			t_arr_index = is_in_t_arr_dic_str(shell->bcmd, arr[i]);
			if (t_arr_index != -1)
			{
				c          = true;
				token->type = TOKEN_BCMD;
				i          = attribute_cmd_subtokens(shell, token, i, count_args_cmd(shell, i));
			}
		}

		// CMD ? 
		if (!c)
		{
			token->value = find_command_path(token->value, shell->env);
			if (token->value)
			{
				c          = true;
				token->type = TOKEN_CMD;
				i          = attribute_cmd_subtokens(shell, token, i, count_args_cmd(shell, i));
			}
			else
				token->value = arr[i];
		}

		// WORD
		if (token->type == TOKEN_WORD)
		{
			token->u.all_parts.n_parts = count_subtokens(token->value);
			attribute_subtoken_type(token);
		}

		if (token->type != TOKEN_OPER)
		{
			add_cmd(shell, token);
			shell->n_cmd++;
		}

		i++;
		idx_token++;
	}
}*/
