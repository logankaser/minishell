/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:23:15 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:23:16 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned		i;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	if (n < 1)
		return (0);
	while (i < n)
	{
		if (a[i] < b[i])
			return (a[i] - b[i]);
		if (a[i] > b[i])
			return (a[i] - b[i]);
		++i;
	}
	return (0);
}
