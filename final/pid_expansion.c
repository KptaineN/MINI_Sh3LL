/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:23:17 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 12:27:20 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
// »»-----► Number of lines: 58
void  **pid_expansion(void **v_arr, t_list *env)
{
	int n;
	int i= 0;
	char *p;
	char ** arr = (char **)v_arr;
	
	while(arr[i])
	{
		n = 0;
		p = arr[i];
		while(1)
		{
			p = ft_strchr(p,'$');
			if (!p)
				break;
			if (*(p+1) == '$')
			{	
				p+=2;
				n++;
			}
			else if (!*(p+1))
				break;
			else
				p++;
		}
		if (n != 0)
		{
			char *s_pid = get_env_value(env, "PID");
			int l_pid = ft_strlen(s_pid);
			int len = (l_pid-2)*n+ft_strlen(arr[i]);
			char *new = malloc(len+1);

			char *s = arr[i];
			int idx = 0;
			while (*s)
			{
				p = ft_strchr(s,'$');
				if (!p)
					break;
				if (*(p+1) == '$')
				{
					ft_strncpy(new+idx,s,(unsigned int)(p-s));
					idx = (unsigned int)(p-s);
					ft_strcpy(new+idx,s_pid);
					idx+=l_pid;
					s = p+2;
				}
				else
					s = p+1;
			}
			ft_strcpy(new+idx,s);
			new[len] = 0;
			free(arr[i]);	
			arr[i] = new;
		}
		i++;
	}
	return v_arr;
}