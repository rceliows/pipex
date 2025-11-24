#include "../inc/pipex_bonus.h"

void	command_null(t_pipex *data, pid_t *pids)
{
	if (pids)
		free(pids);
	write(STDERR_FILENO, "pipex: permission denied: \n", 28);
	cleanup_data(data);
	exit(126);
}

void	close_unused_pipes(t_pipex *data, int cmd_index)
{
	int	i;

	i = 0;
	while (i < data->num_commands - 1)
	{
		if (i != cmd_index - 1 && i != cmd_index)
		{
			close(data->pipes[i][0]);
			close(data->pipes[i][1]);
		}
		i++;
	}
}

void	execute_command(t_pipex *data, int cmd_index, pid_t *pids)
{
	if (!data->cmds[cmd_index] || !data->cmds[cmd_index][0]
			|| !data->cmds[cmd_index][0][0])
		command_null(data, pids);
	else
	{
		if (*(data->cmd_is_exec[cmd_index]) && data->cmd_paths[cmd_index])
			execve(data->cmd_paths[cmd_index],
				data->cmds[cmd_index], data->envp);
		if (data->cmds[cmd_index] && data->cmds[cmd_index][0])
			execve(data->cmds[cmd_index][0], data->cmds[cmd_index], data->envp);
	}
	command_not_found(data->cmds[cmd_index][0], data, pids);
}

void	setup_infile(t_pipex *data, pid_t *pids)
{
	int	devnull;

	data->infile = open(data->infile_name, O_RDONLY);
	if (data->infile == -1)
	{
		devnull = open("/dev/null", O_RDONLY);
		if (devnull != -1)
		{
			if (dup2(devnull, STDIN_FILENO) == -1)
				error_exit("dup2");
			close(devnull);
		}
		else
			close(STDIN_FILENO);
		if (access(data->infile_name, F_OK) == -1)
			file_not_existing(data->infile_name, data, pids);
		else
			file_not_accessible(data->infile_name, data, pids);
	}
	else
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
			error_exit("dup2");
		close(data->infile);
	}
}
