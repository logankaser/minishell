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

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

extern char	**environ;

t_map	g_env;

void	b_echo(t_vector args)
{
	(void)args;
}

void	b_cd(t_vector args)
{
	(void)args;
}

void	b_env(t_vector args)
{
	(void)args;
}

void	b_setenv(t_vector args)
{
	(void)args;
}

void	b_unsetenv(t_vector args)
{
	(void)args;
}

void	b_exit(t_vector args)
{
	(void)args;
}

void	init_minishell(t_minishell *ms)
{
	unsigned	i;
	t_envvar	*var;

	ft_map_init(&ms->builtins, 0);
	ft_map_init(&g_env, 0);
	i = 0;
	while(environ[i])
	{
		var = malloc(sizeof(t_envvar));
		var->data = ft_strdup(environ[i++]);
		var->value = ft_strchr(var->data, '=');;
		*(var->value) = '\0';
		ft_map_insert(&g_env, var->data, var);
		*(var->value) = '=';
		var->value += 1;
	}
	ft_map_insert(&ms->builtins, "echo", &b_echo);
	ft_map_insert(&ms->builtins, "cd", &b_cd);
	ft_map_insert(&ms->builtins, "env", &b_env);
	ft_map_insert(&ms->builtins, "setenv", &b_setenv);
	ft_map_insert(&ms->builtins, "unsetenv", &b_unsetenv);
	ft_map_insert(&ms->builtins, "exit", &b_exit);
	ft_printf("Map count: %u\n", g_env.count);
}

int	main(int argc, char** argv)
{
	char		*line;
	int			ret;
	pid_t		pid;
	t_minishell ms;

	init_minishell(&ms);
	line = NULL;
	ft_printf("%s) ", ((t_envvar*)ft_map_get(&g_env, "USER"))->value);
	(void)argc;
	while (1)
	{
		ret = get_next_line(0, &line);
		ft_striter_1(line, (char (*)(char))ft_tolower);
		if (!ft_strncmp("exit", line, 4))
			exit(1);
		else if (!ft_strncmp("fork", line, 4))
		{
			pid = fork();
			if (pid == 0)
			{
				lseek(STDIN_FILENO, 0, SEEK_END);
				execv("/bin/cat", argv);
				printf("Failed to execute command\n");
			}
			else
				waitpid(pid, 0, 0);
		}
		ft_printf("%s) ", ((t_envvar*)ft_map_get(&g_env, "USER"))->value);
		ft_memdel((void**)&line);
	}
	return (0);
}
