/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:09:55 by rceliows          #+#    #+#             */
/*   Updated: 2025/06/30 12:09:57 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <signal.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		**pipes;
	size_t		num_commands;
	int		**cmd_is_exec;
	char	***cmds;
	char	**cmd_paths;
	char	**envp;
	char	*infile_name;
	char	*outfile_name;
	int		is_here_doc;
}	t_pipex;

// Core functions
void	init_data(t_pipex *data, int argc, char **argv, char **envp);
void	initialize_data_fields(t_pipex *data,
			int argc, char **argv, char **envp);
void	initialize_array_pointers(t_pipex *data);
void	execute_multiple_pipelines(t_pipex *data);
char	*command_path(char *cmd, char **envp);
void	execute_command(t_pipex *data, int cmd_index, pid_t *pids);
void	close_unused_pipes(t_pipex *data, int cmd_index);
int		allocate_pipes(t_pipex *data);
int		allocate_arrays(t_pipex *data);

// Pipeline setup functions
void	setup_first_command(t_pipex *data, pid_t *pids);
void	setup_middle_command(t_pipex *data, int cmd_index, pid_t *pids);
void	setup_last_command(t_pipex *data, pid_t *pids);
void	setup_command(char **cmd, char **cmd_path,
			int *is_exec, char **envp);
void	setup_infile(t_pipex *data, pid_t *pids);

// Here_doc functions
int		is_here_doc(char *first_arg);
void	setup_here_doc(t_pipex *data, char *limiter);
void	init_here_doc_data(t_pipex *data, int argc, char **argv, char **envp);
void	setup_here_doc_output(t_pipex *data);

// Command path resolution
char	*find_command_start(char **envp);
char	*join_path_and_cmd(char *dir, char *cmd);
char	*full_command_path(char **paths, char *cmd);
char	*search_in_env_path(char *cmd, char **envp);
char	*search_in_default_paths(char *cmd);
size_t		skip_quoted_section(char *argv, size_t *i);
size_t		skip_braced_section(char *argv, size_t *i);
size_t		extract_quoted_content(char *argv, size_t *i, size_t *start);
size_t		extract_regular_content(char *argv, size_t *i, size_t *start);

// Shell parsing
char	**shell_parser(char *argv);
char	*allocate_and_copy(char *argv, size_t start, size_t len);
char	**handle_empty_input(void);
char	**parse_arguments(char *argv, size_t arg_count);

// Error handling
void	command_not_found(char *cmd, t_pipex *data, pid_t *pids);
void	error_exit(char *msg);
void	strderr_exit(char *msg, t_pipex *data);
void	file_not_accessible(char *file, t_pipex *data, pid_t *pids);
void	file_not_existing(char *file, t_pipex *data, pid_t *pids);
void	fork_fail(t_pipex *data, pid_t pid, pid_t *pids);
void	handle_file_error(t_pipex *data);
void	malloc_error_backup(char *cmd, char *file, char *null, t_pipex *data);
void	command_null(t_pipex *data, pid_t *pids);

// Memory management
void	free_string_array(char **array, size_t num_cmds);
void	free_int_array(int **array, size_t size);
void	cleanup_data(t_pipex *data);
int		allocate_cmd_exec_array(t_pipex *data);

#endif
