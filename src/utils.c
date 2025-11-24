#include "../inc/pipex_bonus.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	strderr_exit(char *msg, t_pipex *data)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	cleanup_data(data);
	exit(EXIT_FAILURE);
}

void	free_string_array(char **array, int num_cmds)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	if (num_cmds)
	{
		while (i < num_cmds)
		{
			free(array[i]);
			i++;
		}
	}
	else
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	free(array);
}

void	free_int_array(int **array, int size)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

void	cleanup_data(t_pipex *data)
{
	size_t	i;

	if (!data)
		return ;
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	if (data->pipes)
		free_int_array(data->pipes, data->num_commands - 1);
	if (data->cmd_is_exec)
		free_int_array(data->cmd_is_exec, data->num_commands);
	if (data->cmds)
	{
		i = 0;
		while (i < data->num_commands && data->cmds[i])
		{
			free_string_array(data->cmds[i], 0);
			i++;
		}
		free(data->cmds);
	}
	if (data->cmd_paths)
		free_string_array(data->cmd_paths, data->num_commands);
	free(data);
}
