/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:59:22 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 19:59:24 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parameter Expansion
** Expands the largest possible valid name where a name matches
** the regular expression (^[A-Za-z_]+[A-Za-z0-9_]*$)
** ${NAME} is also valid, in which case brackets are matched and any ASCII
** characters can be used.
*/

static size_t	expand_var(const char *raw, t_uvector *out, t_minishell *ms)
{
	size_t		i;
	char		*name;
	t_envvar	*var;

	if (ft_isdigit(raw[0]) || !(ft_isalpha(raw[0]) || ANY2(raw[0], '_', '{')))
		return (0);
	i = 0;
	if (raw[0] == '{')
	{
		while (raw[i] && raw[i] != '}')
			++i;
		name = ft_strsub(raw, 1, i - 1);
		var = ft_map_get(&ms->env, name);
		ft_string_append(out, var ? var->value : "");
		free(name);
		return (i + 2);
	}
	while (ft_isalpha(raw[i]) || raw[i] == '_')
		++i;
	name = ft_strsub(raw, 0, i);
	var = ft_map_get(&ms->env, name);
	ft_string_append(out, var ? var->value : "");
	free(name);
	return (i + 1);
}

/*
** Tilde Expansion
** Supports only basic `~` -> `$HOME`
** functionality for now
** Later will support more complete tilde expansion.
*/

static size_t	expand_tilde(const char *raw, t_uvector *out, t_minishell *ms)
{
	t_envvar	*var;

	(void)raw;
	var = ft_map_get(&ms->env, "HOME");
	ft_string_append(out, var ? var->value : "");
	return (1);
}

/*
** Expansion dispatch
** i.e `$<varname>` `~<user>`
**
** Expansion functions return how many chars
** of input the expansion consumed
**
** For example, expand_var("PLACE/bin", out, ms) returns `5`,
** because the expansion function consumes five chars, "PLACE".
*/

char			*expand(const char *raw, t_minishell *ms)
{
	t_uvector	str;
	unsigned	i;
	unsigned	skip;
	size_t		len;

	ft_uvector_init(&str, 1);
	i = 0;
	len = ft_strlen(raw);
	while (i < len)
	{
		skip = 0;
		if (raw[i] == '$')
			skip = expand_var(raw + i + 1, &str, ms);
		else if (raw[i] == '~')
			skip = expand_tilde(raw + i + 1, &str, ms);
		i += skip;
		if (skip == 0)
			ft_uvector_push(&str, raw + i++);
	}
	ft_uvector_push(&str, "\0");
	return ((char*)str.data);
}
