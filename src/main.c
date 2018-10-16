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

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

extern char	**environ;

void	init_minishell(t_minishell *ms)
{
	int	i;

	*ms = (t_minishell){0, 0};
	i = -1;
	while(environ[++i])
		if (!ft_strncmp("USER=", environ[i], 5))
			ms->user = ft_strdup(environ[i] + 5);
		else if (!ft_strncmp("PATH=", environ[i], 5))
			ms->path = ft_strdup(environ[i] + 5);
}

int	main(void)
{
	char *line;
	int ret;
	t_minishell ms;

	init_minishell(&ms);
	line = NULL;
	ft_printf("%s) ", ms.user);
	while (1)
	{
		ret = get_next_line(0, &line);
		if (!ft_strncmp("path", line, 4))
			ft_printf("PATH=%s\n", ms.path);
		ft_printf("%s) ", ms.user);
		ft_memdel((void**)&line);
	}
	return (0);
}
