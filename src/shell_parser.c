#include "../inc/pipex_bonus.h"

static int	command_count(char *argv)
{
	int	count;
	size_t	i;

	i = 0;
	count = 0;
	while (argv[i])
	{
		while (argv[i] == ' ')
			i++;
		if (argv[i] == '\0')
			break ;
		if (argv[i] == '\'' || argv[i] == '"')
			count += skip_quoted_section(argv, &i);
		else if (argv[i] == '{')
			count += skip_braced_section(argv, &i);
		else
		{
			while (argv[i] && argv[i] != ' ')
				i++;
			count++;
		}
	}
	return (count);
}

static int	extract_braced_content(char *argv, int *i, int *start)
{
	size_t	len;
	unsigned int	brace_count;

	*start = *i;
	len = 1;
	(*i)++;
	brace_count = 1;
	while (argv[*i] && brace_count > 0)
	{
		if (argv[*i] == '{')
			brace_count++;
		else if (argv[*i] == '}')
			brace_count--;
		(*i)++;
		len++;
	}
	return (len);
}

static int	extract_content(char *argv, int *i, int *start)
{
	if (argv[*i] == '\'' || argv[*i] == '"')
		return (extract_quoted_content(argv, i, start));
	else if (argv[*i] == '{')
		return (extract_braced_content(argv, i, start));
	else
		return (extract_regular_content(argv, i, start));
}

char	*cmd_prep(char *argv, int *i)
{
	size_t	start;
	size_t	len;

	while (argv[*i] == ' ')
		(*i)++;
	len = extract_content(argv, i, &start);
	return (allocate_and_copy(argv, start, len));
}

char	**shell_parser(char *argv)
{
	int		arg_count;

	if (!argv || !argv[0])
		return (handle_empty_input());
	arg_count = command_count(argv);
	if (arg_count == 0)
		return (NULL);
	return (parse_arguments(argv, arg_count));
}
