/*

full gpt vue que je connais pas trop cette shit

*/

#define _POSIX_C_SOURCE 200809L
#include "../../include/minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <stdio.h>
#include <unistd.h>

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);  // Efface la ligne courante (readline)
	rl_on_new_line();        // Prépare readline à afficher une nouvelle ligne
	rl_redisplay();          // Réaffiche le prompt
}

void	handle_sigquit(int sig)
{
	(void)sig;
	// Tu peux choisir d'afficher ou non quelque chose, 
	// mais pour minishell, on n'affiche rien sur SIGQUIT dans le shell parent.
}

/*void	init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = &handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;

	sa_quit.sa_handler = &handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;

	sigaction(SIGINT, &sa_int, NULL);   // Ctrl+C
	sigaction(SIGQUIT, &sa_quit, NULL); // Ctrl+
}*/
void	init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = &handle_sigint;
	sa_int.sa_flags = SA_RESTART;

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN; // on ignore Ctrl+\ (SIGQUIT)
	sa_quit.sa_flags = 0;

	sigaction(SIGINT, &sa_int, NULL);   // Ctrl+C
	sigaction(SIGQUIT, &sa_quit, NULL); // Ctrl+quit
}


