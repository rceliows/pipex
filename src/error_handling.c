#include "../inc/pipex_bonus.h"

static void	write_atomic_error(const char *prefix,
			const char *msg, const char *suffix)
{
	size_t		len;
	size_t		i;
	char		buffer[1024];

	len = 0;
	i = 0;
	while (prefix && prefix[i] && len < 1020)
		buffer[len++] = prefix[i++];
	i = 0;
	while (msg && msg[i] && len < 1020)
		buffer[len++] = msg[i++];
	i = 0;
	while (suffix && suffix[i] && len < 1023)
		buffer[len++] = suffix[i++];
	buffer[len] = '\0';
	write(STDERR_FILENO, buffer, len);
}

void	command_not_found(char *cmd, t_pipex *data, pid_t *pids)
{
	if (pids)
		free(pids);
	write_atomic_error("pipex: command not found: ", cmd, "\n");
	cleanup_data(data);
	exit(127);
}

void	file_not_accessible(char *file, t_pipex *data, pid_t *pids)
{
	if (pids)
		free(pids);
	write_atomic_error("pipex: permission denied: ", file, "\n");
	cleanup_data(data);
	exit(13);
}

void	file_not_existing(char *file, t_pipex *data, pid_t *pids)
{
	if (pids)
		free(pids);
	write_atomic_error("pipex: no such file or directory: ", file, "\n");
	cleanup_data(data);
	exit(2);
}

void	fork_fail(t_pipex *data, pid_t pid, pid_t *pids)
{
	size_t	i;

	if (pids)
		free(pids);
	i = 0;
	perror("pipex");
	if (pid > 0)
		kill(pid, SIGTERM);
	while (i < data->num_commands - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	cleanup_data(data);
	exit(EXIT_FAILURE);
}
