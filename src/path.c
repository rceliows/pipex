#include "../inc/main.h"

char	*find_command_start(char **envp)
{
	char		*path_env;
	size_t		i;

	i = 0;
	path_env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_env);
}

char	*join_path_and_cmd(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	if (!dir || !cmd)
		return (NULL);
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

char	*full_command_path(char **paths, char *cmd)
{
	char		*full_path;
	size_t		i;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = join_path_and_cmd(paths[i], cmd);
		if (!full_path)
		{
			free_string_array(paths, 0);
			return (NULL);
		}
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_string_array(paths, 0);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_string_array(paths, 0);
	return (NULL);
}
