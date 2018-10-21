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

void	ft_map_init(t_map *m, unsigned key_size, unsigned size)
{
	m->data = ft_memalloc(sizeof(t_list*) * size);
	m->count = 0;
	m->capacity = size;
	m->key_size = key_size;
}

/*
** Current implementation is chaining based,
** Reuses the 42 list struct by storing the hash in the
** content_size field, which allows the reuse of all the t_lst fucntions.
*/

void	ft_map_insert(t_map *m, const char *key, void *ptr)
{
	uint32_t	hash;

	hash = m->key_size ? ft_fnv_32((uint8_t*)key, m->key_size)
		: ft_fnv_32((uint8_t*)key, ft_strlen(key));
	ft_map_insert_(m, hash, ptr);
	if (m->count / (double)m->capacity >= 0.7)
	{
		printf("resize load_factor: %lf\n", m->count / (double)m->capacity);
		ft_map_resize_(m, m->capacity * 2 + 1);
	}
}

void	ft_map_remove(t_map *m, const char *key)
{
	uint32_t	hash;
	t_list		*i;
	t_list		*tmp;

	hash = m->key_size ? ft_fnv_32((uint8_t*)key, m->key_size)
		: ft_fnv_32((uint8_t*)key, ft_strlen(key));
	if (!(i = m->data[hash % m->capacity]))
		return ;
	if (i->content_size == hash)
	{
		free(i->content);
		m->data[hash % m->capacity] = i->next;
		free(i);
		--m->count;
		return ;
	}
	while (i->next && i->next->content_size != hash)
		i = i->next;
	if (!i->next)
		return ;
	free(i->next->content);
	tmp = i->next;
	i->next = i->next->next;
	free(tmp);
	--m->count;
}

void	*ft_map_get(t_map *m, const char *key)
{
	uint32_t	hash;
	t_list		*i;

	hash = m->key_size ? ft_fnv_32((uint8_t*)key, m->key_size)
		: ft_fnv_32((uint8_t*)key, ft_strlen(key));
	i = m->data[hash % m->capacity];
	while (i)
	{
		if (i->content_size == hash)
			return (i->content);
		i = i->next;
	}
	return (NULL);
}

void	ft_map_del(t_map *m)
{
	unsigned	i;
	t_list		*link;
	t_list		*tmp;

	i = 0;
	while (i < m->capacity)
	{
		if (!(link = m->data[i++]))
			continue ;
		while (link)
		{
			free(link->content);
			tmp = link;
			link = link->next;
			free(tmp);
		}
	}
}