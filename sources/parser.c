#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "parser.h"
#include "config.h"

char * epurate_string(const char *to_epurate)
{
	char *epurated;
	char *tmp;

	if (to_epurate == NULL)
		return NULL;

	epurated = malloc(sizeof(char) * strlen(to_epurate) +  sizeof(char));
	tmp = epurated;

	if (epurated == NULL)
		return NULL;

	while (*to_epurate)
	{
		if (*to_epurate != ' ' && *to_epurate != '\t'
		    && *to_epurate != '\n')
			*tmp++ = *to_epurate;
		to_epurate++;
	}

	*tmp = 0;

	return epurated;
}

int is_comment(const char *to_check)
{
	if (to_check == NULL)
		return -EINVAL;

	if (*to_check == COMMENT || *to_check == '\0')
		return 1;

	return 0;
}

char * get_token(char *to_parse, const char *delim)
{
	return strtok(to_parse, delim);
}
