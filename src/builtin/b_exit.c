/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:00:45 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/25 20:00:46 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern volatile	sig_atomic_t g_running;

int				b_exit(int argc, char *argv[], t_minishell *ms)
{
	(void)argv;
	(void)ms;
	if (argc != 1)
	{
		ft_printf("usage: exit\n");
		return (1);
	}
	g_running = FALSE;
	return (0);
}
