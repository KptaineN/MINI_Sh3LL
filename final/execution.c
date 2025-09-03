/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:54:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/02 12:17:29 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minish.h"

static bool apply_redir(char ***arg, int *i, t_arr *oper)
{
    char **expanded = *arg;
    int idx_oper = is_in_t_arr_dic_str(oper,expanded[*i]);
    int (*f)(void *, int *);
    if (idx_oper != -1)
    {
        f = ((t_dic *)oper->arr[idx_oper])->value;
        if (!expanded[(*i)+1] || idx_oper == 4)
            perror("nothing after operator");
        free(expanded[(*i)]);
        expanded[(*i)++] = NULL;
        if (f != NULL)
            f(expanded[(*i)],0);
        free(expanded[(*i)]);
        expanded[(*i)] = NULL;
        return 1;
    }
    else
        return 0;
}

static char **final_cmd_line(char ***arg, int count, int len)
{
    char **expanded = *arg;
    char **result = NULL;
    result = malloc(sizeof(char *)*(count+1));
    int i = 0;
    int j = 0;
    while(i < len)
    {
        if (expanded[i] != NULL)
            result[j++] = expanded[i];
        i++;  
    }
    result[j] = 0;
    free(expanded);
    expanded = NULL;
    return result;
}

char **expansion_partition_redirection(t_list *cmd, t_list *env, t_arr *oper)
{
    char **expanded = expand_variables((char **)cmd->arr_content,env);
    //display_string_array(expanded);
    //char *a = expanded[0];
    //char *b = expanded[1];
    //char *c = expanded[2];
    //char *d = expanded[3];
    //(void)a;
    //(void)b;
    //(void)c;
    //(void)d;
    int i = 0;
    int count = 0;
    
    while(expanded[i])
    {
        if (!apply_redir(&expanded, &i, oper))
            count++;
        i++;
    }
    if (count == 0)
        return 0;
    return final_cmd_line(&expanded,count,i);
}