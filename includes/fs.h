#ifndef FS_H
#define FS_H

#include "config.h"
#include "dirent.h"

/*
 * Sort the given struct dirent ** on their names.
 * The sorting is alphabetical
 * @a:	first struct dirent ** to sort
 * @b:	second struct dirent ** to sort
 */
int alpha_sort(const struct dirent **a, const struct dirent **b);

/*
 * Filter the given struct dirent on it's type.
 * Files are allowed , everything else rejected.
 * @entry:	struct dirent to filter in or out
 */
int filter(const struct dirent *entry);

/*
 * Retreive the endpoint entries in the directory pointed by @path
 * This function does no verify the validity of the file content
 * @path:	path to the directory where the search will occur.
 */
struct dirent ** get_edp_entries(const char *path);

/*
 * Release the endpoint entries pointed by *@entries[x] by calling free() on each of
 * them. Then by calling free on the parent array @entries.
 */
void release_edp_entries(struct dirent **entries);

/*
 * Builds a path from a directory path and a filename
 * ex: (1) /etc/spatch (2) my_file -> (3) /etc/spatch/my_file
 * @directory:	directory
 * @filename:	filename
 */
char * build_file_path(const char *directory, const char *filename);

#endif
