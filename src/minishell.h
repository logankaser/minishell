/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 18:53:53 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/14 18:55:03 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <limits.h>
# include "libft.h"

/*
** Memory layout of t_envar:
**
** "NAMEOFVAR=VALUE:VALUE:VALUE"
**  ^         ^
**  |         |
** data*    value*
**.
*/

typedef struct	s_envvar
{
	char*		data;
	char*		value;
}				t_envvar;


typedef struct	s_minishell
{
	t_map		builtins;
	t_map		path;
	t_map		env;
	t_bool		running;
	char		pwd[PATH_MAX];
	char		old_pwd[PATH_MAX];
}				t_minishell;

typedef int (*t_builtin)(int argc, char *argv[], t_minishell *ms);

/*
** Functions.
*/

char			**map_to_env_array(t_map *env, t_bool sort);
char			*expand(const char *raw, t_minishell *ms);
void			run_commands_semicolon(t_minishell *ms, char *line);
void			update_path(t_minishell *ms);

#endif
