
#include "../../include/minishell.h"

char	*get_env_value(t_env *env, const char *name)
{
	size_t n;
	
	n = ft_strlen(name);

	while (env)
	{
		if (ft_strncmp(env->key, name, n) == 0 && env->key[n] == '\0')
			return (env->value);
		env = env->next;
	}
	return (NULL);
}