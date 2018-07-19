/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:25:22 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:25:23 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char		*copy;
	unsigned	len;
	unsigned	i;

	len = ft_strlen(str);
	NULL_GUARD(copy = malloc(len + 1));
	i = 0;
	while (i < len)
		copy[i++] = *str++;
	copy[i] = '\0';
	return (copy);
}
