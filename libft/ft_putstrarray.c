/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrarray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:24:28 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:24:30 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrarray(char **str)
{
	ft_putstr("[ ");
	while (*str)
	{
		ft_putchar('\"');
		ft_putstr(*str);
		ft_putchar('\"');
		++str;
		if (*str)
			ft_putstr(", ");
	}
	ft_putstr(" ]");
	ft_putchar('\n');
}
