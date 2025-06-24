/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:19 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/24 15:24:44 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Initialize operator handlers array
/*
	Exemple d'utilité
	// To execute a pipe operator at token index 3
	execute_operator(shell, 3);

	// Or directly call a specific handler
	shell->oper_handlers[4](shell, 3); // Index 4 is pipe in the array
*/
void init_operator_handlers(t_shell *shell)
{
	int i = 0;
	// Array of function pointers corresponding to all_operators array
	int (*operator_handlers[])(void *, int) = {
		handle_heredoc,     // "<<"
		handle_append,      // ">>"
		handle_and,         // "&&"
		handle_or,          // "||"
		handle_pipe,        // "|"
		handle_redirect_in, // "<"
		handle_redirect_out // ">"
	};
	
	// Store operator handlers in shell structure
	shell->oper_handlers = malloc(sizeof(void (*)(void *, int)) * shell->oper->len);
	if (!shell->oper_handlers)
		return;
	
	while (i < shell->oper->len)
	{
		shell->oper_handlers[i] = operator_handlers[i];
		i++;
	}
}

// initialise the builtins and operators
void init_all_t_arr(t_shell *shell)
{
	char *all_operators[] = {"<<",">>","&&","||","|","<",">",NULL};
	char *all_builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	build_t_arr(&shell->bcmd, all_builtins, ft_arrlen(all_builtins));
	build_t_arr(&shell->oper, all_operators, ft_arrlen(all_operators));
	init_operator_handlers(shell);
}


void	init_minishell(t_minishell *shell, char **envp)
{
	shell->args = NULL;     // Initialize command arguments to NULL
	shell->input = NULL;    // Initialize user input to NULL
	shell->exit_status = 0; // Initialize exit status to 0
	shell->ast = NULL;      // Initialize the AST to NULL
	shell->env = NULL;      // Initialize the environment linked list to NULL
	if (!shell || !envp)
		return ; // Check for NULL pointers
	shell->env = init_env(envp);
	// Initialize the environment linked list dans env_list
	shell->args = NULL;
	shell->input = NULL;
	shell->exit_status = 0;
	shell->ast = NULL; // Initialize the AST to NULL
						// Initialize other components as needed
						// For example, set up signal handlers,
						// initialize data structures, etc.
	init_all_t_arr(&shell->parser);
}

/*loop principal dans mainloop.c*/

int	start_minishell(t_minishell *shell, char **envp)
{
	if (!shell || !envp)
		return (0);
	

	//t_shell *shell;
	//	shell = malloc(sizeof(t_shell));
	//	if (!shell)
	//		return 0;
	ft_memset(shell, 0, sizeof(t_shell));
	
	init_minishell(shell, envp);
	looping(shell);
	// Here,
	//	you can add any additional initialization steps needed for your minishell
	// Additional initialization steps can be added here
	// For example, setting up signal handlers, initializing the AST, etc.
	return (1); // Return 1 on success
}
