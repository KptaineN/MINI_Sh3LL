/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:27 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/16 15:43:47 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Objectif du lexer.c

    Lire une line (ex: echo hello | grep h > out.txt)

    Découper en tokens :

        commandes/arguments (echo, hello, grep, h)

        opérateurs (|, >, <, >>, <<)

    Respecter les quotes (', ")

    Sauter les espaces non significatifs

    Remplir une liste chaînée de t_token

    2. Fonctions à implémenter dans lexer.c
a. t_token *lexer(const char *line);

    Fonction principale : découpe line en tokens et retourne la liste chaînée.

b. void add_token(t_token **head, t_token_type type, const char *value);

    Ajoute un token à la liste (avec malloc).

c. char *read_word(const char *line, int *i);

    Lit un mot classique (jusqu’à espace ou opérateur), gère les quotes.

d. t_token_type get_operator_type(const char *line, int *i);

    Détecte |, <, >, <<, >>.

    Exemple simplifié d’implémentation (esquisse)

t_token *lexer(const char *line)
{
	t_token *tokens = NULL;
	int i = 0;

	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '\'' || line[i] == '"')
		{
			char *quoted = read_quoted_string(line, &i);
			add_token(&tokens, WORD, quoted);
			free(quoted);
		}
		else if (is_operator(line[i]))
		{
			t_token_type type = get_operator_type(line, &i);
			add_token(&tokens, type, ft_substr(line, i - 1, (type == APPEND || type == HEREDOC) ? 2 : 1));
		}
		else
		{
			char *word = read_word(line, &i);
			add_token(&tokens, WORD, word);
			free(word);
		}
	}
	return tokens;
}

🔧 Fonctions utiles à coder aussi

    int is_operator(char c) → vérifie si c est |, <, >

    char *read_word(...) → lit un mot normal

    char *read_quoted_string(...) → gère contenu entre quotes

    void add_token(...) → alloue et ajoute le token à la liste

À retenir

    Le lexer ne comprend pas la grammaire (pas encore d’arbre ou de syntaxe).

    Il découpe uniquement en morceaux significatifs (tokenisation).

    Il faut être robuste aux quotes et redirections doubles (>>, <<).

*/