/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isanyof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:21:48 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/20 14:49:06 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isanyof(char c, const char *these)
{
	while (*these)
		if (*these++ == c)
			return (TRUE);
	return (FALSE);
}
