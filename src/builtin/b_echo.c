/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:00:32 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 20:00:33 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	b_echo(int argc, char *argv[], t_minishell *ms)
{
	int			i;
	t_bool		flag_n;

	(void)ms;
	flag_n = 0;
	i = 1;
	if (i < argc && argv[i][0] == '-' && argv[i][1] == 'n')
		flag_n = ++i;
	while (i < argc)
		if (i + 1 < argc)
			ft_printf("%s ", argv[i++]);
		else
			ft_printf("%s", argv[i++]);
	if (!flag_n)
		ft_putchar('\n');
	return (0);
}
