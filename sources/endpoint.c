#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "fs.h"
#include "user.h"
#include "endpoint.h"
#include "parser.h"

int load_endpoints(struct list_head  *head, const char *path)
{
	struct dirent **edp_entries;
	struct endpoint *edp;
	char *c_path;
	int i;

	edp_entries = get_edp_entries(path);

	if (edp_entries == NULL)
		return -ENOMEM;

	for (i = 0; edp_entries[i]; i++)
	{
		edp = calloc(1, sizeof(*edp));

		if (edp == NULL)
			return -ENOMEM;

		INIT_LIST_HEAD(&(edp->endpoints));
		INIT_LIST_HEAD(&(edp->allowed_users));
		c_path = build_file_path(path, edp_entries[i]->d_name);

		if (c_path == NULL)
			return -ENOMEM;

		if (parse_endpoint(edp, c_path))
		{
			__delete_endpoint(edp);
			free(edp);
		}
		else
			list_add_back(&(edp->endpoints), head);

		free(c_path);
	}

	release_edp_entries(edp_entries);
	return 0;
}

int parse_endpoint(struct endpoint *edp, const char *path)
{
	FILE *fp;
	char *line;
	size_t size;
	char *line_epurated;
	int status;


	fp = fopen(path, "r");
	line = NULL;
	size = 0;
	status = 0;

	if (fp == NULL)
		return errno;

	while (getline(&line, &size, fp) != -1)
	{
		line_epurated = epurate_string(line);
		free(line);

		if (line_epurated == NULL)
			return -ENOMEM;

		if (is_comment(line_epurated) == 0)
			status = parse_line(edp, line_epurated);

		free (line_epurated);
		line = NULL;
		size = 0;

		if (status)
			break;
	}

	if (line)
		free(line);

	if (fclose(fp) != 0)
		return errno;

	return status;
}

int delete_endpoints(struct list_head *head)
{
	int count;
	struct list_head *pos;
	struct list_head *n;
	struct endpoint *edp;

	count = 0;

	LIST_FOR_EACH(pos, n, head)
	{
		edp = LIST_ENTRY(pos, struct endpoint, endpoints);
		if (__delete_endpoint(edp) == 0)
			count = count +1;
		list_del(&edp->endpoints);
		free(edp);
	}

	return count;
}

int __delete_endpoint(struct endpoint *edp)
{
	struct list_head *pos;
	struct list_head *n;
	struct user *allowed_user;

	if (edp == NULL)
		return -EINVAL;

	free(edp->hostname);
	free(edp->username);
	free(edp->password);

	LIST_FOR_EACH(pos, n, &edp->allowed_users)
	{
		allowed_user = LIST_ENTRY(pos, struct user, users);
		free(allowed_user->username);
		list_del(&allowed_user->users);
		free(allowed_user);
	}

	return 0;
}

int parse_line(struct endpoint *edp, char *line)
{
	char *token;

	token = strtok(line, "=");

	if (token == NULL)
		return -EINVAL;

	if (strcmp(token, HOSTNAME) == 0)
		return parse_hostname(edp, strtok(NULL, "="));

	else if (strcmp(token, USERNAME) == 0)
		return parse_username(edp, strtok(NULL, "="));

	else if (strcmp(token, PASSWORD) == 0)
		return parse_password(edp, strtok(NULL, "="));

	else if (strcmp(token, PORT) == 0)
		return parse_port(edp, strtok(NULL, "="));

	else if (strcmp(token, ALLOWED_USERS) == 0)
		return parse_allowed_users(edp, strtok(NULL, "="));

	return -EINVAL;
}

int parse_hostname(struct endpoint *edp, const char *token)
{
	if (edp == NULL || token == NULL)
		return -EINVAL;

	if (strlen(token) == 0)
		return -EINVAL;

	edp->hostname = strdup(token);

	if (edp->hostname == NULL)
		return -ENOMEM;

	return 0;
}


int parse_username(struct endpoint *edp, const char *token)
{
	if (edp == NULL || token == NULL)
		return -EINVAL;

	if (strlen(token) == 0)
		return -EINVAL;

	edp->username = strdup(token);

	if (edp->username == NULL)
		return -ENOMEM;

	return 0;
}

int parse_password(struct endpoint *edp, const char *token)
{
	if (edp == NULL || token == NULL)
		return -EINVAL;

	if (strlen(token) == 0)
		return -EINVAL;

	edp->password = strdup(token);

	if (edp->password == NULL)
		return -ENOMEM;

	return 0;
}

int parse_port(struct endpoint *edp, const char *token)
{
	if (edp == NULL || token == NULL)
		return -EINVAL;

	if (strlen(token) == 0)
		return -EINVAL;

	if (sscanf(token , "%d", &(edp->port)) != 1)
		return -EINVAL;

	return 0;
}

int parse_allowed_users(struct endpoint *edp, char *token)
{
	struct user *allowed_user;
	char *username;

	if (edp == NULL || token == NULL)
		return -EINVAL;

	if (strlen(token) == 0)
		return -EINVAL;

	while ((username = strtok(token, ",")) != NULL)
	{
		if (token)
			token = NULL;

		allowed_user = calloc(1, sizeof(struct user));

		if (allowed_user == NULL)
			return -ENOMEM;

		allowed_user->username = strdup(username);

		if (allowed_user == NULL)
			return -ENOMEM;

		list_add_back(&(allowed_user->users), &(edp->allowed_users));

	}

	return 0;
}

int parse_allowed_groups(struct endpoint *edp, char *token)
{
}
