# Pipex

A C implementation of shell pipelines that mimics the behavior of the Unix pipe (`|`) operator, allowing you to chain multiple commands together.

## Description

Pipex executes a series of commands in a pipeline, where the output of each command becomes the input of the next command. The program reads from an input file, processes it through multiple commands, and writes the result to an output file.

This project replicates the shell command:
```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2
```

## Features

- **Multiple Command Pipeline**: Chain together any number of commands
- **Here-doc Support**: Alternative input mode using heredoc syntax
- **Shell-style Parsing**: Handles quoted arguments, braces, and complex command strings
- **Flexible Path Resolution**: Searches for executables in PATH and default directories
- **Error Handling**: Comprehensive error messages for missing files, permissions, and invalid commands
- **Memory Safe**: Proper cleanup of all allocated resources

## Installation

### Prerequisites

- `gcc` or compatible C compiler
- `make`
- Git (for cloning libft dependency)

### Building

Clone the repository and build the project:

```bash
git clone <repository-url>
cd pipex
make
```

The Makefile will automatically:
1. Clone the required `libft` library if not present
2. Compile all source files
3. Create the `pipex` executable

## Usage

### Normal Mode

```bash
./pipex file1 cmd1 cmd2 [cmd3 ...] file2
```

**Example:**
```bash
./pipex infile "ls -l" "wc -l" outfile
```

This is equivalent to:
```bash
< infile ls -l | wc -l > outfile
```

### Here-doc Mode

```bash
./pipex here_doc LIMITER cmd1 cmd2 [cmd3 ...] file
```

**Example:**
```bash
./pipex here_doc EOF "grep hello" "wc -w" outfile
```

This reads input from stdin until "EOF" is encountered, then processes it through the commands.

## Command Parsing

Pipex supports advanced shell-style command parsing:

- **Quoted arguments**: `"ls -la"` or `'grep "pattern"'`
- **Braced expressions**: `{echo,test}`
- **Complex commands**: `"awk '{print $1}' file.txt"`
- **Multiple arguments**: Each command string is parsed into separate arguments

## Exit Codes

The program returns the exit status of the last command in the pipeline:

- `0`: Success
- `2`: File not found
- `13`: Permission denied
- `126`: Command cannot execute
- `127`: Command not found
- `128+N`: Terminated by signal N

## Project Structure

```
pipex/
├── inc/
│   └── main.h                          # Header file with structures and prototypes
├── src/
│   ├── main.c                          # Entry point and mode selection
│   ├── init_data.c                     # Data structure initialization
│   ├── init_data_utils.c               # Helper functions for initialization
│   ├── execute_multiple_pipelines.c    # Main pipeline execution logic
│   ├── execute_multiple_pipelines_utils.c   # Command setup functions
│   ├── execute_multiple_pipelines_utils_2.c # Additional execution utilities
│   ├── here_doc.c                      # Here-doc functionality
│   ├── path.c                          # Command path resolution
│   ├── shell_parser.c                  # Command string parsing
│   ├── shell_parser_utils.c            # Parsing helper functions
│   ├── shell_parser_utils_2.c          # Additional parsing utilities
│   ├── error_handling.c                # Error reporting functions
│   └── utils.c                         # Memory management and cleanup
├── libft/                              # Custom C library (auto-cloned)
├── Makefile                            # Build configuration
└── README.md                           # This file
```

## Implementation Details

### Pipeline Architecture

1. **Data Initialization**: Parses arguments and sets up command structures
2. **Pipe Creation**: Allocates and creates pipes for inter-process communication
3. **Process Forking**: Creates child processes for each command
4. **File Descriptor Management**: Sets up stdin/stdout redirections
5. **Command Execution**: Executes commands via `execve`
6. **Cleanup**: Waits for all processes and cleans up resources

### Key Components

- **t_pipex structure**: Contains all pipeline state (file descriptors, pipes, commands)
- **Shell parser**: Handles quoted strings and complex argument parsing
- **Path resolver**: Searches for executables in PATH and default locations
- **Error handler**: Atomic error writing to prevent race conditions

## Make Targets

- `make` or `make all`: Build the project
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make fcleanall`: Remove everything including libft
- `make re`: Rebuild the project
- `make reall`: Full rebuild including libft

## Examples

### Basic Pipeline
```bash
./pipex input.txt "cat" "grep error" "wc -l" output.txt
```

### Multiple Commands
```bash
./pipex data.csv "cat" "cut -d, -f1" "sort" "uniq" result.txt
```

### Here-doc with Grep
```bash
./pipex here_doc END "grep test" "wc -l" count.txt
test line 1
another test
END
```

### Complex Commands
```bash
./pipex file.txt "awk '{print $2}'" "sort -n" "head -5" top5.txt
```

## Error Handling

The program handles various error conditions:

- **File errors**: Missing or inaccessible input files
- **Command errors**: Non-existent or non-executable commands
- **System errors**: Fork failures, pipe failures, memory allocation failures
- **Permission errors**: Lack of read/write/execute permissions

All errors are reported to stderr with descriptive messages.

## Memory Management

Pipex implements careful memory management:

- All dynamically allocated memory is freed before exit
- File descriptors are properly closed
- Child processes clean up their resources
- No memory leaks under normal operation

## Notes

- The program requires at least 2 commands (3 in here-doc mode)
- Commands are executed in separate processes using fork
- The last command's exit status becomes the program's exit status
- Input file errors in normal mode redirect stdin to `/dev/null` for subsequent commands

## License

This project is part of the 42 school curriculum.

## Author

Created as part of the 42 Network pipex project.
