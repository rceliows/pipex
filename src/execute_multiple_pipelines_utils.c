#include "../inc/pipex_bonus.h"

static void	setup_first_command_input(t_pipex *data, pid_t *pids)
{
	int	devnull;

	if (data->is_here_doc)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
			error_exit("dup2");
		close(data->infile);
		return ;
	}
	if (!data->infile_name)
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
		return ;
	}
	setup_infile(data, pids);
}

static void	setup_last_command_output(t_pipex *data)
{
	if (data->is_here_doc)
		data->outfile = open(data->outfile_name,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->outfile = open(data->outfile_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		error_exit("dup2");
	close(data->outfile);
}

void	setup_first_command(t_pipex *data, pid_t *pids)
{
	setup_first_command_input(data, pids);
	if (data->num_commands == 1)
	{
		if (data->is_here_doc)
			data->outfile = open(data->outfile_name,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			data->outfile = open(data->outfile_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			error_exit("dup2");
		close(data->outfile);
	}
	else
	{
		if (dup2(data->pipes[0][1], STDOUT_FILENO) == -1)
			error_exit("dup2");
		close(data->pipes[0][1]);
		close(data->pipes[0][0]);
		close_unused_pipes(data, 0);
	}
	execute_command(data, 0, pids);
}

void	setup_middle_command(t_pipex *data, int cmd_index, pid_t *pids)
{
	if (dup2(data->pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
		error_exit("dup2");
	close(data->pipes[cmd_index - 1][0]);
	close(data->pipes[cmd_index - 1][1]);
	if (dup2(data->pipes[cmd_index][1], STDOUT_FILENO) == -1)
		error_exit("dup2");
	close(data->pipes[cmd_index][1]);
	close(data->pipes[cmd_index][0]);
	close_unused_pipes(data, cmd_index);
	execute_command(data, cmd_index, pids);
}

void	setup_last_command(t_pipex *data, pid_t *pids)
{
	int	last_cmd_index;

	last_cmd_index = data->num_commands - 1;
	if (dup2(data->pipes[last_cmd_index - 1][0], STDIN_FILENO) == -1)
		error_exit("dup2");
	close(data->pipes[last_cmd_index - 1][0]);
	close(data->pipes[last_cmd_index - 1][1]);
	setup_last_command_output(data);
	close_unused_pipes(data, last_cmd_index);
	execute_command(data, last_cmd_index, pids);
}
