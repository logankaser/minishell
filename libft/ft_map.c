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

typedef struct      s_list
{
    void            *content;
    size_t          content_size;
    struct s_list   *next;
}                   t_list;
t_list              *ft_lstnew(void const *content, size_t content_size);
void                ft_lstdelone(t_list **lst, void (*del)(void *, size_t));
void                ft_lstdel(t_list **lst, void (*del)(void *, size_t));
void                ft_lstadd(t_list **lst, t_list *new);
void                ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list              *ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void                *ft_lstpush(t_list **lst, void *content, size_t size);
void                *ft_lstpop(t_list **lst);
t_list              *ft_lstfind(t_list *lst, t_compare pred, const void *data);
void                ft_lstrm(t_list **lst, t_list *to_rm);


uint64_t			ft_fnv_64(uint8_t *data, size_t size);
uint32_t			ft_fnv_32(uint8_t *data, size_t size);

typedef struct	  s_map
{
	t_list		  **data;
	unsigned		count;
	unsigned		capacity;
}				   t_map;

*/

void	ft_map_init(t_map *m)
{
	m->data = ft_memalloc(sizeof(void*) * 16);
	m->count = 0;
	m->capacity = 0;
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

void	ft_map_insert(t_map *m, const char *key, const void *d)
{
}

void	ft_map_remove(t_map *m, const char *key)
{
}

void	ft_map_del(t_map *m)
{
}
