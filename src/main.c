#include "../inc/pipex_bonus.h"

static void	start_fail(t_pipex *data)
{
	ft_putstr_fd("Usage:\n", STDERR_FILENO);
	ft_putstr_fd("  ./pipex file1 cmd1 cmd2 ... cmdn file2\n", STDERR_FILENO);
	ft_putstr_fd("  ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file\n",
		STDERR_FILENO);
	free(data);
	exit(EXIT_FAILURE);
}

static void	handle_here_doc_mode(t_pipex *data, int argc,
					char **argv, char **envp)
{
	size_t	i;

	init_here_doc_data(data, argc, argv, envp);
	data->is_here_doc = 1;
	setup_here_doc(data, argv[2]);
	if (!allocate_arrays(data))
		strderr_exit("Error: Memory allocation failed\n", data);
	i = 0;
	while (i < data->num_commands)
	{
		data->cmds[i] = shell_parser(argv[3 + i]);
		if (!data->cmds[i])
			strderr_exit("Error: Command parsing failed\n", data);
		setup_command(data->cmds[i], &(data->cmd_paths[i]),
			data->cmd_is_exec[i], envp);
		i++;
	}
	if (!allocate_pipes(data))
		strderr_exit("Error: Pipe creation failed\n", data);
}

static void	handle_normal_mode(t_pipex *data, int argc,
					char **argv, char **envp)
{
	data->is_here_doc = 0;
	init_data(data, argc, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*data;

	data = malloc(sizeof(t_pipex));
	if (!data)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (is_here_doc(argv[1]))
	{
		if (argc < 5)
			start_fail(data);
		handle_here_doc_mode(data, argc, argv, envp);
	}
	else
	{
		if (argc < 5)
			start_fail(data);
		handle_normal_mode(data, argc, argv, envp);
	}
	execute_multiple_pipelines(data);
	return (0);
}
