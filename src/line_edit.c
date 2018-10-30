/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 15:53:26 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/28 15:53:27 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t g_clear;

static void	autocomplete(t_uvector *line, t_minishell *ms)
{
	unsigned	i;
	t_list		*link;
	char		*best;
	char		*tmp;

	i = 0;
	best = NULL;
	while (i < ms->path.capacity)
		if ((link = ms->path.data[i++]))
			while (link)
			{
				tmp = ft_strrchr(link->content, '/');
				if (tmp && !ft_strncmp((char*)line->data, tmp + 1, line->length)
					&& (!best || ft_strlen(tmp + 1) < ft_strlen(best)))
					best = tmp + 1;
				link = link->next;
			}
	if (!best)
		return ;
	ft_uvector_push(line, "\0");
	ft_putstr(best + line->length - 1);
	ft_string_append(line, best + line->length - 1);
	ft_uvector_pop(line, NULL);
}

t_bool		read_line(t_uvector *line, t_minishell *ms)
{
	char in;

	in = 0;
	read(STDIN_FILENO, &in, 1);
	if (in == '\n')
	{
		ft_uvector_push(line, "\0");
		line->length = 0;
		write(STDOUT_FILENO, "\n", 1);
		return (TRUE);
	}
	else if (in == ms->terminal_settings.c_cc[VERASE] && line->length)
	{
		write(STDOUT_FILENO, "\b \b", 3);
		ft_uvector_pop(line, NULL);
	}
	else if (ft_isprint(in))
	{
		write(STDOUT_FILENO, &in, 1);
		ft_uvector_push(line, &in);
	}
	else if (in == '\t' && line->length > 0)
		autocomplete(line, ms);
	return (FALSE);
}
