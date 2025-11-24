#include "../inc/pipex_bonus.h"

static	pid_t	fork_and_execute_command(t_pipex *data,
			int cmd_index, pid_t *pids)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fork_fail(data, pid, pids);
	if (pid == 0)
	{
		if (cmd_index == 0)
			setup_first_command(data, pids);
		else if (cmd_index == data->num_commands - 1)
			setup_last_command(data, pids);
		else
			setup_middle_command(data, cmd_index, pids);
	}
	return (pid);
}

static void	close_all_pipes(t_pipex *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_commands - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
}

static void	wait_for_all_children(t_pipex *data, pid_t *pids)
{
	size_t	i;
	int	status;
	int	last_status;
	int	exit_status;

	i = 0;
	last_status = 0;
	while (i < data->num_commands)
	{
		waitpid(pids[i], &status, 0);
		if (i == data->num_commands - 1)
			last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		exit_status = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		exit_status = 128 + WTERMSIG(last_status);
	else
		exit_status = EXIT_FAILURE;
	free(pids);
	cleanup_data(data);
	exit(exit_status);
}

static	pid_t	*allocate_pids_array(t_pipex *data)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * data->num_commands);
	if (!pids)
	{
		perror("malloc");
		cleanup_data(data);
		exit(EXIT_FAILURE);
	}
	return (pids);
}

void	execute_multiple_pipelines(t_pipex *data)
{
	pid_t	*pids;
	size_t		i;

	pids = allocate_pids_array(data);
	i = 0;
	while (i < data->num_commands)
	{
		pids[i] = fork_and_execute_command(data, i, pids);
		i++;
	}
	close_all_pipes(data);
	wait_for_all_children(data, pids);
}
