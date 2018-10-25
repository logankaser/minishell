#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "minishell.h"

static void	scan_dir_for_executables(t_uvector *tmp_str, DIR *dir,
	char *dir_path, t_map *path)
{
	struct dirent	*file;
	struct stat		file_info;
	unsigned		len;

	tmp_str->length = 0;
	ft_string_append(tmp_str, dir_path);
	len = tmp_str->length;
	while ((file = readdir(dir)))
	{
		tmp_str->length = len;
		ft_string_append(tmp_str, "/");
		ft_string_append(tmp_str, file->d_name);
		if (file->d_name[0] == '.' || access((char*)tmp_str->data, X_OK))
			continue ;
		stat((char*)tmp_str->data, &file_info);
		if (!S_ISREG(file_info.st_mode))
			continue ;
		free(ft_map_remove(path, file->d_name));
		ft_map_set(path, file->d_name, ft_strdup((char*)tmp_str->data));
	}
}

void	update_path(t_minishell *ms)
{
	t_envvar		*var_path;
	char			**path_array;
	unsigned		i;
	DIR				*dir;
	t_uvector		tmp_str;

	ft_uvector_init(&tmp_str, sizeof(char));
	if (!(var_path = ft_map_get(&ms->env, "PATH")))
		return ;
	path_array = ft_strsplit(var_path->value, ':');
	i = 0;
	while (path_array[i])
	{
		if (!(dir = opendir(path_array[i])))
		{
			free(path_array[i++]);
			continue ;
		}
		scan_dir_for_executables(&tmp_str, dir, path_array[i], &ms->path);
		closedir(dir);
		free(path_array[i++]);
	}
	free(path_array);
	free(tmp_str.data);
}