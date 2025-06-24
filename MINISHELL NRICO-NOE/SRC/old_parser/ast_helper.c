
#include "../../include/minishell.h"


void print_ast(t_ast *node, int level)
{
	if (!node)
		return;

	for (int i = 0; i < level; i++)
		printf("    ");

	switch (node->type)
	{
		case NODE_COMMAND:
			printf("COMMAND:");
			for (int i = 0; node->args && node->args[i]; i++)
				printf(" %s", node->args[i]);
			printf("\n");
			break;
		case NODE_PIPE:
			printf("PIPE\n");
			break;
		case NODE_REDIR_OUT:
			printf("> %s\n", node->filename);
			break;
		case NODE_REDIR_APPEND:
			printf(">> %s\n", node->filename);
			break;
		case NODE_REDIR_IN:
			printf("< %s\n", node->filename);
			break;
		case NODE_HEREDOC:
			printf("<< %s\n", node->filename);
			break;
		case NODE_AND:
			printf("&&\n");
			break;
		case NODE_OR:
			printf("||\n");
			break;
		default:
			printf("UNKNOWN NODE (%d)\n", node->type);
			break;
	}
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}


// Helpers AST
/*t_ast	*init_ast_node(t_node_type type)
{
	t_ast *node = malloc(sizeof(t_ast));
	if (!node) return NULL;
	node->type = type;
	node->args = NULL;
	node->filename = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}*/

t_ast *init_command_node(char **args)
{
	t_ast *node = init_ast_node(NODE_COMMAND);
	if (!node) return NULL;
	// Duplique le tableau d’arguments
	int i, count = 0;
	while (args && args[count]) count++;
	node->args = malloc(sizeof(char*) * (count + 1));
	if (!node->args) { free(node); return NULL; }
	for (i = 0; i < count; i++)
		node->args[i] = ft_strdup(args[i]);
	node->args[count] = NULL;
	return node;
}
/*
t_ast *init_redirection_node(t_node_type type, const char *filename, t_ast *child)
{
	t_ast *node = init_ast_node(type);
	if (!node) return NULL;
	node->filename = ft_strdup(filename);
	node->left = child;
	return node;
}*/

