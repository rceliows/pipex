#include "../inc/pipex_bonus.h"

static void	read_here_doc_content(char *limiter, int write_fd)
{
	char	*line;
	char	*limiter_with_newline;
	size_t		limiter_len;

	limiter_len = ft_strlen(limiter);
	limiter_with_newline = ft_strjoin(limiter, "\n");
	if (!limiter_with_newline)
		error_exit("malloc");
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter_with_newline, limiter_len + 1) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
	}
	free(limiter_with_newline);
	close(write_fd);
}

void	setup_here_doc(t_pipex *data, char *limiter)
{
	int		here_doc_pipe[2];
	pid_t	pid;

	if (pipe(here_doc_pipe) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
	{
		close(here_doc_pipe[0]);
		read_here_doc_content(limiter, here_doc_pipe[1]);
		cleanup_data(data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(here_doc_pipe[1]);
		data->infile = here_doc_pipe[0];
		waitpid(pid, NULL, 0);
	}
}

int	is_here_doc(char *first_arg)
{
	if (!first_arg)
		return (0);
	return (ft_strncmp(first_arg, "here_doc", 8) == 0
		&& first_arg[8] == '\0');
}

void	init_here_doc_data(t_pipex *data, int argc, char **argv, char **envp)
{
	data->infile = -1;
	data->outfile = -1;
	data->pipes = NULL;
	data->cmds = NULL;
	data->cmd_paths = NULL;
	data->cmd_is_exec = NULL;
	data->infile_name = NULL;
	data->outfile_name = argv[argc - 1];
	data->envp = envp;
	data->num_commands = argc - 4;
}

void	setup_here_doc_output(t_pipex *data)
{
	data->outfile = open(data->outfile_name,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		error_exit("dup2");
	close(data->outfile);
}
