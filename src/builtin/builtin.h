/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:20:23 by lkaser            #+#    #+#             */
/*   Updated: 2018/10/26 20:20:26 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "minishell.h"

int	b_cd(int argc, char *argv[], t_minishell *ms);
int	b_echo(int argc, char *argv[], t_minishell *ms);
int	b_env(int argc, char *argv[], t_minishell *ms);
int	b_exit(int argc, char *argv[], t_minishell *ms);
int	b_path(int argc, char *argv[], t_minishell *ms);
int	b_setenv(int argc, char *argv[], t_minishell *ms);
int	b_unsetenv(int argc, char *argv[], t_minishell *ms);

#endif
