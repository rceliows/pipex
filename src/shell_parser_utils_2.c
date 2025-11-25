#include "../inc/main.h"

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
