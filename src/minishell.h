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

typedef void (*t_builtin)(t_vector args);

typedef struct	s_envvar
{
	char*		data;
	char*		value;
}				t_envvar;


typedef struct	s_minishell
{
	t_map		builtins;
}				t_minishell;


#endif
