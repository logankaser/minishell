/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:24:06 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:24:07 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putmem(char *varname, void *var, size_t bytes)
{
	unsigned	i;
	char		*str;

	str = (char *)var;
	ft_putstr(varname);
	write(1, " = \"", 4);
	i = 0;
	while (i < bytes)
	{
		if (str[i])
			write(1, str + i, 1);
		else
			write(1, ".", 1);
		++i;
	}
	write(1, "\"\n", 2);
}
