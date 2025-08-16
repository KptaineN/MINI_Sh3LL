#include "../../include/minishell.h"


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

/*
 * Build a linked list of command tokens from the array of tokens
 * produced during parsing. Only command or builtin tokens are kept
 * and the resulting list is stored in shell->cmd_head.
 */
void build_cmd_list(t_shell *shell)
{
    t_token *prev;
    int     i;

    if (!shell || !shell->tokens)
        return ;
    shell->cmd_head = NULL;
    shell->cmd_tail = NULL;
    shell->n_cmd = 0;
    prev = NULL;
    i = 0;
    while (i < shell->n_tokens)
    {
        t_token *tok = &shell->tokens[i];
        if (tok->type == TOKEN_CMD || tok->type == TOKEN_BCMD)
        {
            if (prev)
                prev->next = tok;
            tok->next = NULL;
            add_cmd(shell, tok);
            prev = tok;
            shell->n_cmd++;
        }
        i++;
    }
}

int count_args_cmd(t_shell *shell, int i)
{
    int     n_args;
    char    **arr;
    int     len;
    int     idx_oper;
    char    *op;

    if (!shell || !shell->parsed_args || !shell->parsed_args->arr)
        return 0;
    arr = (char **)shell->parsed_args->arr;
    len = shell->parsed_args->len;
    n_args = 0;
    while (i < len && arr[i])
    {
        idx_oper = is_in_t_arr_dic_str(shell->oper, arr[i]);
        if (idx_oper != -1)
        {
            if (idx_oper < 2 || idx_oper > 4)
            {
                op = ((t_dic *)shell->oper->arr[idx_oper])->key;
                if ((int)ft_strlen(arr[i]) == (int)ft_strlen(op))
                    i++;
                i++;
                continue;
            }
            break;
        }
        n_args++;
        i++;
    }
    if (n_args == 0)
        return 1;
    return n_args;
}