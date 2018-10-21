/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 18:14:20 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/23 09:05:56 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	map_place_link(void **new, unsigned bucket, t_list *link)
{
	t_list		*i;
	if (!new[bucket])
	{
		new[bucket] = link;
		return ;
	}
	i = new[bucket];
	while (i->next)
		i = i->next;
	i->next = link;
	link->next = NULL;
}

void		ft_map_resize_(t_map *m, unsigned size)
{
	void		**new;
	unsigned	i;
	t_list		*link;

	new = ft_memalloc(sizeof(t_list*) * size);
	i = 0;
	while (i < m->capacity)
	{
		if (!(link = m->data[i++]))
			continue ;
		while (link)
		{
			map_place_link(new, link->content_size % size, link);
			link = link->next;
		}
	}
	free(m->data);
	m->data = new;
	m->capacity = size;
}


/*
** Reuses the 42 list struct by storing the hash in the
** content_size field, which allows the reuse of all the t_lst fucntions.
*/

void		ft_map_insert_(t_map *m, uint32_t hash, void *ptr)
{
	t_list		*i;
	unsigned	bucket;

	bucket = hash % m->capacity;
	if (!m->data[bucket])
	{
		ft_lstpush((t_list **)m->data + bucket, ptr, hash);
		++m->count;
	}
	else
	{
		i = m->data[bucket];
		while (i->next && i->next->content_size != hash)
			i = i->next;
		if (!i->next)
		{
			i->next = ft_lstnew(NULL, 0);
			++m->count;
		}
		i->next->content_size = hash;
		i->next->content = ptr;
	}
}