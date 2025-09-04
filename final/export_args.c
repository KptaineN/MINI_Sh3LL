/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:55:45 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/04 14:02:48 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	is_valid_identifier(const char *name)
{
	int	i;

	i = 0;
	if (!name || !*name)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	handle_arg_with_assignment(char *arg, t_sh *sh)
{
	char	*eq;
	int		ret;

	eq = ft_strchr(arg, '=');
	ret = 0;
	*eq = '\0';
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minish: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		exit_status = 1;
		ret = 1;
	}
	else if (set_env_var(sh, arg, eq + 1) != 0)
		ret = 1;
	*eq = '=';
	return (ret);
}

int	handle_arg_without_assignment(char *arg, t_sh *sh)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minish: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		exit_status = 1;
		return (1);
	}
	if (!find_env_var(sh, arg))
		return (set_env_var(sh, arg, NULL));
	return (0);
}

int	process_export_argument(char *arg, t_sh *sh)
{
	if (ft_strchr(arg, '='))
		return (handle_arg_with_assignment(arg, sh));
	return (handle_arg_without_assignment(arg, sh));
}

void	ft_bubble_str_sort(char **arr)
{
    int		i;
    int		swapped;
    char	*tmp;

    if (!arr)
        return;
    do
    {
        swapped = 0;
        i = 0;
        while (arr[i] && arr[i + 1])
        {
            if (ft_strcmp(arr[i], arr[i + 1]) > 0)
            {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                swapped = 1;
            }
            i++;
        }
    } while (swapped);
}

int	export_no_arguments(t_sh *sh)
{
	char	**arr;

	arr = env_to_array(sh);
	if (!arr)
	{
		exit_status = 1;
		return (1);
	}
	ft_bubble_str_sort(arr);
	print_export_arr(arr);
	free_string_array(arr);
	exit_status = 0;
	return (0);
}