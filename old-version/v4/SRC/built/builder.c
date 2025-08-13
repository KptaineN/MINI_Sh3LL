// SRC/exec/argv_builder.c
#include "../../include/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_buf {
    char  *s;
    size_t len;
    size_t cap;
} t_buf;

static int buf_grow(t_buf *b, size_t add)
{
    if (b->len + add + 1 <= b->cap) return 0;
    size_t ncap = b->cap ? b->cap : 32;
    while (ncap < b->len + add + 1) ncap <<= 1;
    char *ns = realloc(b->s, ncap);
    if (!ns) return -1;
    b->s = ns; b->cap = ncap;
    return 0;
}

static int buf_add(t_buf *b, const char *s, size_t n)
{
    if (!s || n == 0) return 0;
    if (buf_grow(b, n) < 0) return -1;
    memcpy(b->s + b->len, s, n);
    b->len += n;
    b->s[b->len] = '\0';
    return 0;
}

static int is_name_char(int c) { return (ft_isalnum(c) || c == '_'); }

static int expand_dollars(t_shell *sh, const char *s, size_t n, t_buf *out)
{
    size_t i = 0;
    while (i < n) {
        if (s[i] != '$') {
            size_t j = i;
            while (j < n && s[j] != '$') j++;
            if (buf_add(out, s + i, j - i) < 0) return -1;
            i = j;
            continue;
        }
        i++; // skip '$'
        if (i >= n) { // '$' final → littéral
            if (buf_add(out, "$", 1) < 0) return -1;
            break;
        }
        if (s[i] == '?') { // $?
            char tmp[32];
            int m = snprintf(tmp, sizeof(tmp), "%d", sh->exit_status);
            if (m < 0 || buf_add(out, tmp, (size_t)m) < 0) return -1;
            i++;
            continue;
        }
        if (!is_name_char((unsigned char)s[i])) {
            if (buf_add(out, "$", 1) < 0) return -1;
            continue;
        }
        size_t k = i;
        while (k < n && is_name_char((unsigned char)s[k])) k++;
        // lookup env interne exact (terminer la clé temporairement)
        char key[256];
        size_t klen = k - i;
        if (klen >= sizeof(key)) klen = sizeof(key) - 1;
        memcpy(key, s + i, klen);
        key[klen] = '\0';
        const char *val = find_env_value(sh->env, key);
        if (val) {
            if (buf_add(out, val, strlen(val)) < 0) return -1;
        } // sinon → vide (comme bash)
        i = k;
    }
    return 0;
}

static char *join_container_to_arg(t_shell *sh, t_subtoken_container *c)
{
    t_buf b = {0};
    for (int i = 0; i < c->n_parts; i++) {
        t_subtoken *p = &c->parts[i];
        if (!p->p || p->len <= 0) continue;
        if (p->type == QUOTE_SINGLE) {
            if (buf_add(&b, p->p, (size_t)p->len) < 0) { free(b.s); return NULL; }
        } else {
            if (expand_dollars(sh, p->p, (size_t)p->len, &b) < 0) { free(b.s); return NULL; }
        }
    }
    if (!b.s) {
        b.s = ft_strdup("");
        if (!b.s) return NULL;
    }
    return b.s;
}

char **token_to_argv(t_shell *sh, t_token *tok)
{
    (void)sh;
    if (!tok || tok->n_args <= 0 || !tok->cmd_args_parts) return NULL;
    int n = tok->n_args;
    char **argv = calloc(n + 1, sizeof(char *));
    if (!argv) return NULL;
    for (int i = 0; i < n; i++) {
        argv[i] = join_container_to_arg(sh, &tok->cmd_args_parts[i]);
        if (!argv[i]) {
            for (int k = 0; k < i; k++) free(argv[k]);
            free(argv);
            return NULL;
        }
    }
    argv[n] = NULL;
    return argv;
}

void free_argv(char **argv)
{
    if (!argv) return;
    for (int i = 0; argv[i]; i++) free(argv[i]);
    free(argv);
}
