#include "../inc/main.h"

char	*allocate_and_copy(char *argv, size_t start, size_t len)
{
	char	*cmd;
	size_t	j;

	cmd = malloc(len + 1);
	if (!cmd)
		return (NULL);
	j = 0;
	while (j < len)
	{
		cmd[j] = argv[start + j];
		j++;
	}
	cmd[len] = '\0';
	return (cmd);
}

size_t	skip_quoted_section(char *argv, size_t *i)
{
	char	quote;

	quote = argv[(*i)++];
	while (argv[*i] && argv[*i] != quote)
		(*i)++;
	if (argv[*i] == quote)
		(*i)++;
	return (1);
}

size_t	skip_braced_section(char *argv, size_t *i)
{
	unsigned int	brace_count;

	(*i)++;
	brace_count = 1;
	while (argv[*i] && brace_count > 0)
	{
		if (argv[*i] == '{')
			brace_count++;
		else if (argv[*i] == '}')
			brace_count--;
		(*i)++;
	}
	return (1);
}

size_t	extract_quoted_content(char *argv, size_t *i, size_t *start)
{
	char	quote;
	size_t	len;

	quote = argv[(*i)++];
	*start = *i;
	len = 0;
	while (argv[*i] && argv[*i] != quote)
	{
		(*i)++;
		len++;
	}
	if (argv[*i] == quote)
		(*i)++;
	return (len);
}

size_t	extract_regular_content(char *argv, size_t *i, size_t *start)
{
	size_t	len;

	*start = *i;
	len = 0;
	while (argv[*i] && argv[*i] != ' ')
	{
		(*i)++;
		len++;
	}
	return (len);
}
