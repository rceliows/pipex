#include "../inc/main.h"

void	initialize_data_fields(t_pipex *data,
			int argc, char **argv, char **envp)
{
	data->infile = -1;
	data->outfile = -1;
	data->pipes = NULL;
	data->cmds = NULL;
	data->cmd_paths = NULL;
	data->cmd_is_exec = NULL;
	data->infile_name = argv[1];
	data->outfile_name = argv[argc - 1];
	data->envp = envp;
	data->num_commands = argc - 3;
	data->is_here_doc = 0;
}

char	*search_in_env_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	path_env = find_command_start(envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = full_command_path(paths, cmd);
	return (full_path);
}

char	*search_in_default_paths(char *cmd)
{
	char		**default_paths;
	char		*full_path;
	size_t		i;

	default_paths = (char *[]){"/bin", "/usr/bin", "/usr/local/bin", NULL};
	i = 0;
	while (default_paths[i])
	{
		full_path = join_path_and_cmd(default_paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	allocate_cmd_exec_array(t_pipex *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_commands)
	{
		data->cmd_is_exec[i] = malloc(sizeof(int));
		if (!data->cmd_is_exec[i])
		{
			while (--i >= 0)
			{
				if (data->cmd_is_exec[i])
					free(data->cmd_is_exec[i]);
			}
			return (0);
		}
		*(data->cmd_is_exec[i]) = 0;
		i++;
	}
	return (1);
}

void	initialize_array_pointers(t_pipex *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_commands)
	{
		data->cmds[i] = NULL;
		data->cmd_paths[i] = NULL;
		data->cmd_is_exec[i] = NULL;
		i++;
	}
}
