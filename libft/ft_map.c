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

void	ft_map_set(t_map *m, const char *key, void *ptr)
{
	uint32_t	hash;

	hash = m->key_size ? ft_fnv_32((uint8_t*)key, m->key_size)
		: ft_fnv_32((uint8_t*)key, ft_strlen(key));
	ft_map_insert(m, hash, ptr);
	if (m->count / (double)m->capacity >= 0.7)
		ft_map_resize_(m, m->capacity * 2 + 1);
}

void	*ft_map_remove(t_map *m, const char *key)
{
	uint32_t	hash;
	t_list		**i;
	void		*value;
	t_list		*next;

	hash = m->key_size ? ft_fnv_32((uint8_t*)key, m->key_size)
		: ft_fnv_32((uint8_t*)key, ft_strlen(key));
	i = (t_list**)m->data + (hash % m->capacity);
	while (*i)
	{
		if ((*i)->content_size == hash)
		{
			value = (*i)->content;
			next = (*i)->next;
			free(*i);
			*i = next;
			--m->count;
			return value;
		}
		*i = (*i)->next;
	}
	return (NULL);
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

void	ft_map_clear(t_map *m, void (*free_fn)(void *))
{
	unsigned	i;
	t_list		*link;
	t_list		*tmp;
	unsigned	count;

	count = 0;
	i = 0;
	while (i < m->capacity)
	{
		if (!(link = m->data[i]))
		{
			++i;
			continue ;
		}
		while (link)
		{
			free_fn(link->content);
			tmp = link;
			link = link->next;
			free(tmp);
		}
		m->data[i] = NULL;
		++i;
	}
	m->count = 0;
}