
#include "../../include/parsking.h"


// Helper function to get PATH from environment
static char	*get_path_env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (1)
	{
		if (strncmp(temp->content, "PATH=", 5) == 0)
			return (temp->content + 5); // Skip "PATH="
		temp = temp->next;
		if (temp == env)
			return (NULL);
	}
	return (NULL);
}

// Helper function to join path and command
static char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = strlen(dir);
	cmd_len = strlen(cmd);
	int i, j;
	full_path = malloc(dir_len + cmd_len + 2); // +2 for '/' and '\0'
	if (!full_path)
		return (NULL);
	// Copy directory
	i = 0;
	while (i < dir_len)
	{
		full_path[i] = dir[i];
		i++;
	}
	// Add separator
	full_path[i++] = '/';
	// Copy command
	j = 0;
	while (j < cmd_len)
	{
		full_path[i + j] = cmd[j];
		j++;
	}
	full_path[i + j] = '\0';
	return (full_path);
}

// Main function to find command path
char	*find_command_path(char *cmd, t_list *env)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*full_path;

	int i, start, len;
	// If command contains '/', it's already a path
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}
	// Get PATH envirnment variable
	path_env = get_path_env(env);
	if (!path_env)
		return (NULL);
	// Make a copy of PATH to work with
	len = strlen(path_env);
	path_copy = malloc(len + 1);
	if (!path_copy)
		return (NULL);
	strcpy(path_copy, path_env);
	// Search through each directory in PATH
	start = 0;
	i = 0;
	while (i <= len)
	{
		if (path_copy[i] == ':' || path_copy[i] == '\0')
		{
			path_copy[i] = '\0'; // Null-terminate current directory
			dir = path_copy + start;
			// Skip empty directories
			if (*dir != '\0')
			{
				full_path = join_path(dir, cmd);
				if (full_path && access(full_path, F_OK | X_OK) == 0)
				{
					free(path_copy);
					return (full_path);
				}
				if (full_path)
					free(full_path);
			}
			start = i + 1;
		}
		i++;
	}
	free(path_copy);
	return (NULL);
}

