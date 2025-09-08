/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:09:23 by nkiefer           #+#    #+#             */
/*   Updated: 2025/09/02 13:33:04 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "minish.h"

int		builtin_export(void *v_sh, void **v_argv);
int		export_no_arguments(t_sh *sh);
int		process_export_argument(char *arg, t_sh *sh);

/* export_utils.c */
char	**env_to_array(t_sh *sh);
void	print_export_arr(char **arr);

/* export_args.c */
int		is_valid_identifier(const char *name);
int		handle_arg_with_assignment(char *arg, t_sh *sh);
int		handle_arg_without_assignment(char *arg, t_sh *sh);

/* export_env.c */
t_list	*find_env_var(t_sh *sh, const char *key);
int		update_env_var(t_list *env, const char *value);
int		create_env_var(t_sh *sh, const char *key, const char *value);
int		set_env_var(t_sh *sh, const char *key, const char *value);

#endif // EXPORT_H
