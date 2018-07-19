/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:25:31 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:25:34 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_string_init(t_string *s)
{
	s->capacity = 4;
	s->content = malloc(4);
	s->length = 0;
	s->content[0] = '\0';
}

size_t		ft_string_append(t_string *s, char *add)
{
	size_t	len;
	char	*new;

	len = ft_strlen(add);
	if (len < 1)
		return (0);
	if (len > s->capacity - s->length)
	{
		new = malloc(((s->length + len) * 2) + 1);
		ft_bzero(new, (s->length + len) * 2 + 1);
		if (!new)
			return (0);
		s->capacity = (s->length + len) * 2;
		ft_memcpy(new, s->content, s->length);
		free(s->content);
		s->content = new;
	}
	ft_memcpy(s->content + s->length, add, len);
	s->length += len;
	return (len);
}

size_t		ft_string_appendn(t_string *s, char *add, size_t len)
{
	char	*new;

	if (len < 1)
		return (0);
	if (len > s->capacity - s->length)
	{
		new = malloc(((s->length + len) * 2) + 1);
		ft_bzero(new, (s->length + len) * 2 + 1);
		if (!new)
			return (0);
		s->capacity = (s->length + len) * 2;
		ft_memcpy(new, s->content, s->length);
		free(s->content);
		s->content = new;
	}
	ft_memcpy(s->content + s->length, add, len);
	s->length += len;
	return (len);
}
