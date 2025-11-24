#include "../inc/pipex_bonus.h"

char	**handle_empty_input(void)
{
	char	**parsed;

	parsed = malloc(sizeof(char *) * 2);
	if (!parsed)
		return (NULL);
	parsed[0] = ft_strdup("");
	if (!parsed[0])
	{
		free(parsed);
		return (NULL);
	}
	parsed[1] = NULL;
	return (parsed);
}

char	**parse_arguments(char *argv, int arg_count)
{
	char	**parsed;
	size_t		i;
	size_t		idx;

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
