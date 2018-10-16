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

/*

uint64_t			ft_fnv_64(uint8_t *data, size_t size);
uint32_t			ft_fnv_32(uint8_t *data, size_t size);

typedef struct	  s_map
{
	t_list		  **data;
	unsigned		count;
	unsigned		capacity;
}				   t_map;

*/

void	ft_map_init(t_map *m, unsigned key_size)
{
	m->data = ft_memalloc(sizeof(t_lst*) * 16);
	m->load = 0;
	m->capacity = 16;
	m->key_size = key_size;
}

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

/*
** Reuses the 42 list struct by storing the hash in the
** size field, which allows the reuse of all the t_lst fucntions.
*/

void	ft_map_insert(t_map *m, const uint8_t *key, const void *ptr)
{
	uint32_t	hash;
	t_lst		*last;
	uint8_t		bucket_load;

	if (m->key_width == 0)
		hash = ft_fnv_32(key, ft_strlen(key));
	else
		hash = ft_fnv_32(key, m->key_width);
	last = ft_lstpush(m->data + (hash % m->capacity), ptr, hash);
}

void	ft_map_remove(t_map *m, const uint8_t *key)
{
}

void	ft_map_del(t_map *m)
{
}
