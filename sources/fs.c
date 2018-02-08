#include <stdlib.h>
#include "string.h"
#include "fs.h"

int alpha_sort(const struct dirent **a, const struct dirent **b)
{
	int result;

	result = strcasecmp((*a)->d_name, (*b)->d_name);
	if (result)
		return -result;
	return strcmp((*a)->d_name, (*b)->d_name);
}

int filter(const struct dirent *entry)
{
	if (entry->d_type == DT_REG)
		return 1;
	return 0;
}


struct dirent ** get_edp_entries(const char *path)
{
	struct dirent **endpoint_files;
	int count;

	count = scandir(path, &endpoint_files, filter, alpha_sort);
	if (count < 0)
		return NULL;
	return endpoint_files;
}

void release_edp_entries(struct dirent **entries)
{
	int i;

	if (entries == NULL)
		return;

	for (i = 0; entries[i]; i++)
		free(entries[i]);

	free(entries);
}

char * build_file_path(const char *directory, const char *filename)
{
	char * c_path;
	int size;

	size = strlen(directory) + strlen(filename) + sizeof(char);

	c_path = malloc(sizeof(char) * size);

	if (c_path == NULL)
		return NULL;

	strcpy(c_path, directory);
	c_path[strlen(directory)] = '/';
	strcpy(&c_path[strlen(directory) + 1], filename);
	return c_path;
}
