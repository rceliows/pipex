#include "../inc/main.h"

char	*command_path(char *cmd, char **envp)
{
	char	*full_path;

	if (!cmd || !cmd[0])
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	if (envp && envp[0])
	{
		full_path = search_in_env_path(cmd, envp);
		if (full_path)
			return (full_path);
	}
	return (search_in_default_paths(cmd));
}

void	setup_command(char **cmd, char **cmd_path,
				int *is_exec, char **envp)
{
	if (cmd && cmd[0] && cmd[0][0])
	{
		*cmd_path = command_path(cmd[0], envp);
		if (*cmd_path != NULL)
			*is_exec = 1;
		else
			*is_exec = 0;
	}
	else
	{
		*cmd_path = NULL;
		*is_exec = 0;
	}
}

int	allocate_arrays(t_pipex *data)
{
	data->cmds = malloc(sizeof(char **) * data->num_commands);
	if (!data->cmds)
		return (0);
	data->cmd_paths = malloc(sizeof(char *) * data->num_commands);
	if (!data->cmd_paths)
		return (0);
	data->cmd_is_exec = malloc(sizeof(int *) * data->num_commands);
	if (!data->cmd_is_exec)
		return (0);
	initialize_array_pointers(data);
	return (allocate_cmd_exec_array(data));
}

int	allocate_pipes(t_pipex *data)
{
	size_t	i;

	data->pipes = malloc(sizeof(int *) * (data->num_commands - 1));
	if (!data->pipes)
		return (0);
	i = 0;
	while (i < data->num_commands - 1)
	{
		data->pipes[i] = NULL;
		i++;
	}
	i = 0;
	while (i < data->num_commands - 1)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
			return (0);
		if (pipe(data->pipes[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

void	init_data(t_pipex *data, int argc, char **argv, char **envp)
{
	size_t	i;

	initialize_data_fields(data, argc, argv, envp);
	if (data->num_commands > 1)
	{
		if (!allocate_arrays(data))
			strderr_exit("Error: Memory allocation failed\n", data);
	}
	else
		data->pipes = NULL;
	i = 0;
	while (i < data->num_commands)
	{
		data->cmds[i] = shell_parser(argv[2 + i]);
		if (data->cmds[i])
			setup_command(data->cmds[i], &(data->cmd_paths[i]),
				data->cmd_is_exec[i], envp);
		i++;
	}
	if (!allocate_pipes(data))
		strderr_exit("Error: Pipe creation failed\n", data);
}
