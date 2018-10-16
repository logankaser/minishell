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

void	ft_map_init(t_map *m, unsigned key_size)
{
	m->data = ft_memalloc(sizeof(t_list*) * 17);
	m->load = 0;
	m->capacity = 17;
	m->key_size = key_size;
}

/*
void	ft_map_resize(t_map *m, unsigned size)
{
	void		**new;
	unsigned	i;

	new = malloc(sizeof(void*) * size);
	i = 0;
	while (i < m->capacity)
	{
		if (m->data[i])
		{
			
		}
		++i;
	}
	free(m->data);
	m->data = new;
	m->capacity = size;
}
*/

/*
** Reuses the 42 list struct by storing the hash in the
** size field, which allows the reuse of all the t_lst fucntions.
*/

void	ft_map_insert(t_map *m, const uint8_t *key, void *ptr)
{
	uint32_t	hash;
	t_list		*i;
	uint8_t		bucket_load;

	if (m->key_size == 0)
		hash = ft_fnv_32(key, ft_strlen((const char*)key));
	else
		hash = ft_fnv_32(key, m->key_size);
	if (!m->data[hash % m->capacity])
		ft_lstpush(m->data + (hash % m->capacity), ptr, hash);
	else
	{
		bucket_load = 1;
		i = m->data[hash % m->capacity];
		while (i->next && i->next->content_size != hash)
		{
			++bucket_load;
			i = i->next;
		}
		ft_printf("bucket %i load: %i\n", hash % m->capacity, bucket_load);
		i->next = ft_lstnew(NULL, 0);
		i = i->next;
		i->content_size = hash;
		i->content = ptr;
	}
}

void	ft_map_remove(t_map *m, const uint8_t *key)
{
	(void)m;
	(void)key;
}

void	*ft_map_get(t_map *m, const uint8_t *key)
{
	uint32_t	hash;
	t_list		*i;

	if (m->key_size == 0)
		hash = ft_fnv_32(key, ft_strlen((const char*)key));
	else
		hash = ft_fnv_32(key, m->key_size);
	i = m->data[hash % m->capacity];
	while (i)
	{
		if (i->content_size == hash)
			return i->content;
		i = i->next;
	}
	return (NULL);
}
