/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:40:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/28 17:14:50 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//dosent use the int i
int handle_heredoc(void *v_token, int i)
{
	t_token *token = v_token;



	return 1;
}

/*
void handle_heredoc(t_shell *shell, int i)
{
  
    // Close previous fd_in to avoid leaks
    if (shell->fd_in != -1 && shell->fd_in != STDIN_FILENO)
        close(shell->fd_in);
      int hd_pipe[2];
    if (pipe(hd_pipe) < 0) {
        perror("pipe");
        return;
    }

    // Check if delimiter is quoted (use your subtoken logic)
    // TRAVAIL: IL FAUT EXPAND !
    char *delimiter =shell->parsed_args->arr[i+1];

    // Read input until delimiter
    char *line;
    while ((line = readline("> "))) { // Requires readline.h
        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        // If not quoted, expand $variables (implement later with your subtoken logic)

        // Write line + newline to pipe
        write(hd_pipe[1], line, strlen(line));
        write(hd_pipe[1], "\n", 1);
        free(line);
    }

    close(hd_pipe[1]); // Close write end
    shell->fd_in = hd_pipe[0]; // Set read end as input
}*/

// "<<",">>","&&","||","|","<",">"
//   0    1   2     3  	4   5   6
void file_access_redirection(t_shell *shell, int t_arr_index, int i)
{
    void **arr = shell->parsed_args->arr;
	if (i+1 >= shell->parsed_args->len)
		perror("Argument manquant pour l'opérateur"); // ERROR
	if (t_arr_index == 5)
	{
		if (shell->fd_in != -1) //<5 
		{
			shell->fd_in = open(arr[i+1], O_RDONLY);
			if (!shell->fd_in)
			 	perror("Erreur lors de l'ouverture en lecture"); // ERROR NOT OPENING;
		}
		else
		{
			if (access(arr[i+1], O_RDONLY) < 0)
				perror("ERROR ACCESS"); // ERROR NOT OPENING;
		}
		return;
	}
	if (t_arr_index == 0 && shell->fd_out != -1) //<< //HEREDOC
	{
		handle_heredoc(shell,i);
        return;
	}

	if (shell->fd_out != -1) // 1>> 6>  
	{
		if (t_arr_index == 1) 
		{
			shell->fd_out = open(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
			if (!shell->fd_out)
				perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
		}
		else if (t_arr_index == 6)
		{
			shell->fd_out = open(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC , 0644);
			if (!shell->fd_out)
				perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
		}
		return;
	}
	if (t_arr_index == 6)
	{
		if (access(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
	}
}

int input_redirection(void *ptr_token,int fd_input)
{
	t_token *token = (t_token *)ptr_token; 
	t_subtoken *c = token->cmd_args_parts[1].parts;
	char *file = ft_strndup((const char *)c->p,c->len);
	int fd_file = open(file, O_RDONLY);
	free(file);
	if (fd_file < -1)
		perror("INPUT REDIRECTION");
	char buffer[1028];	
	int rb = read(fd_file, buffer, 1028);
	while(rb > 0)
	{
		write(fd_input,buffer,rb);
		rb = read(fd_file, buffer, 1028);
	}
	if (rb == -1)
		perror("INPUT REDIRECTION READ");
	close(fd_file);
	return 0;
}

void evaluate_redir(t_shell *shell, t_arr *arr,int write_fd,int read_fd)
{
	int i = 0;
	t_arr *oper = shell->oper;
	t_token *tok;
	int idx;
	(void) write_fd;
	(void) read_fd;
	int (*f)(void *, int);
	while(i<arr->len)
	{
		tok = (t_token *)arr->arr[i];
		
		idx = is_in_t_arr_dic_str(oper, tok->value);
		f = ((t_dic *)oper->arr[idx])->value;
		if (f != NULL)
			f((void *)tok,write_fd);
		i++;
	}
}