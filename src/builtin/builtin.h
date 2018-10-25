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
