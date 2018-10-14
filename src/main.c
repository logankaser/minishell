/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:44:02 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/20 12:46:35 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	char *line;
	int ret;

	line = NULL;
	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret > 0)
			ft_putstr(line);
		ft_memdel((void**)&line);
	}
	return (0);
}
