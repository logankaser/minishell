/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putintarray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:24:02 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:24:04 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putintarray(int *int_array, size_t size)
{
	unsigned i;

	i = 0;
	ft_putstr("[ ");
	while (i < size)
	{
		ft_putnbr(int_array[i++]);
		if (i != size)
			ft_putstr(", ");
	}
	ft_putstr(" ]");
	ft_putchar('\n');
}
