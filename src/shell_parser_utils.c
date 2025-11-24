#include "../inc/pipex_bonus.h"

char	*allocate_and_copy(char *argv, int start, int len)
{
	char	*cmd;
	size_t		j;

	cmd = malloc(len + 1);
	if (!cmd)
		return (NULL);
	j = -1;
	while (++j < len)
		cmd[j] = argv[start + j];
	cmd[len] = '\0';
	return (cmd);
}

int	skip_quoted_section(char *argv, int *i)
{
	char	quote;

	quote = argv[(*i)++];
	while (argv[*i] && argv[*i] != quote)
		(*i)++;
	if (argv[*i] == quote)
		(*i)++;
	return (1);
}

int	skip_braced_section(char *argv, int *i)
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

int	extract_quoted_content(char *argv, int *i, int *start)
{
	char	quote;
	size_t		len;

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

int	extract_regular_content(char *argv, int *i, int *start)
{
	int	len;

	*start = *i;
	len = 0;
	while (argv[*i] && argv[*i] != ' ')
	{
		(*i)++;
		len++;
	}
	return (len);
}
