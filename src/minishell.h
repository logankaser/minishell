/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 18:53:53 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 20:00:15 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <limits.h>
# include <termios.h>
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

typedef struct termios	t_termios;

typedef struct	s_minishell
{
	t_map		builtins;
	t_map		path;
	t_map		env;
	char		pwd[PATH_MAX];
	char		old_pwd[PATH_MAX];
	t_termios	terminal_settings;
}				t_minishell;

typedef int		(*t_builtin)(int argc, char *argv[], t_minishell *ms);

/*
** Functions.
*/

char			**map_to_env_array(t_map *env, t_bool sort);
void			update_path(t_minishell *ms);
void			set_signal_handler(int signum, void (*handler)(int));
void			set_raw_mode(void);
void			prompt(t_minishell *ms);
t_bool			read_line(t_uvector *line, t_minishell *ms);
void			run_commands(t_minishell *ms, char *line);
char			*expand(const char *raw, t_minishell *ms);
void			minishell_cleanup(t_minishell *ms);

#endif
