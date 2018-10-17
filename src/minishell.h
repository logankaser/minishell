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
** Memory layout is like this:
**
** "NAMEOFVAR0VALUE:VALUE:VALUE"
**  ^        ^^
** name*     |\---- value*
**           |
**         (NULL)
**.
*/

typedef struct	s_envvar
{
	char*		name;
	char*		value;
}				t_envvar;

typedef struct	s_minishell
{
	t_map		env;
}				t_minishell;

#endif
