#include "../inc/main.h"

static size_t	command_count(char *argv)
{
	size_t	count;
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

static size_t	extract_braced_content(char *argv, size_t *i, size_t *start)
{
	size_t			len;
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

static size_t	extract_content(char *argv, size_t *i, size_t *start)
{
	if (argv[*i] == '\'' || argv[*i] == '"')
		return (extract_quoted_content(argv, i, start));
	else if (argv[*i] == '{')
		return (extract_braced_content(argv, i, start));
	else
		return (extract_regular_content(argv, i, start));
}

static char	*cmd_prep(char *argv, size_t *i)
{
	size_t	start;
	size_t	len;

	while (argv[*i] == ' ')
		(*i)++;
	len = extract_content(argv, i, &start);
	return (allocate_and_copy(argv, start, len));
}

static char	**parse_arguments(char *argv, size_t arg_count)
{
	char	**parsed;
	size_t	i;
	size_t	idx;

	parsed = malloc(sizeof(char *) * (arg_count + 1));
	if (!parsed)
		return (NULL);
	i = 0;
	idx = 0;
	while (idx < arg_count)
	{
		parsed[idx] = cmd_prep(argv, &i);
		if (!parsed[idx])
		{
			free_string_array(parsed, 0);
			return (NULL);
		}
		idx++;
	}
	parsed[arg_count] = NULL;
	return (parsed);
}

char	**shell_parser(char *argv)
{
	size_t	arg_count;

	if (!argv || !argv[0])
		return (handle_empty_input());
	arg_count = command_count(argv);
	if (arg_count == 0)
		return (NULL);
	return (parse_arguments(argv, arg_count));
}
