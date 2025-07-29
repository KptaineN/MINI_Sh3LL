/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:16 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 14:01:14 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/*** 1) Lecture de l’input ***/
char *read_user_input(void)
{
    char *input = readline("ᕕ( ᐛ )ᕗ minishell$ ");
    if (!input)
        write(1, "exit\n", 5);

    /*
    ** Exemple d'utilisation de get_next_line pour lire plusieurs lignes
    ** et concaténer à l'entrée initiale 
	util pour dquote
	char *line;
	while ((line = get_next_line(STDIN_FILENO))) {
	    char *tmp = ft_strjoin(input, "\n");
	    char *new = ft_strjoin(tmp, line);
	    free(tmp);
	    free(input);
	    free(line);
	    input = new;
	}*/
 
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




int looping(t_minishell *shell)
{
	char  *input;
	char  *step1;
	char  *step2;

	while (1)
	{
		// 1) lire l’input
		input = read_user_input();
		if (!input)
			break;
		if (*input == '\0')
		{
			free(input);
			continue;
		}
		add_history(input);

		// 2) expansion de $?
		step1 = expand_status(input, shell);
		if (!step1)
		{
			free(input);
			continue;
		}

		// 3) expansion des variables
		step2 = replace_variables(step1, shell);
		free(step1);
		if (!step2)
		{
			free(input);
			continue;
		}

		// 4) Parsing avec le vrai parser (custom_split + attribute_token_type)
		shell->parser.input = step2;
		shell->parser.parsed_args = custom_split(step2, &shell->parser);
		if (!shell->parser.parsed_args)
		{
			free(step2);
			free(input);
			continue;
		}
		attribute_token_type(&shell->parser);
		// print_commands(shell->parser.cmd_head);
		shell->parser.pids = malloc(sizeof(pid_t) * shell->parser.n_cmd);
		if (!shell->parser.pids)
			perror("MALLOC pids");
		// 5) Exécution
		launch_process(shell);
		printf("\nlast line\n");
		// 6) Cleanup (ajuster selon ce qui est alloué)
		free_tab((char **)shell->parser.parsed_args->arr);
		free(shell->parser.parsed_args);
		shell->parser.parsed_args = NULL;

		free_tokens(&shell->parser);

		free(step2);
		free(input);
	}
	return (0);
}
