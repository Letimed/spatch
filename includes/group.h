#ifndef GROUP_H
#define GROUP_H

#include "list.h"

/*
 * Structure representing a group :
 * @group_name:	name of the group
 * @groups:	link to the other groups
 * @users:	link to the users contained in the group
 */
struct group
{
	char *group_name;
	struct list_head groups;
	struct list_head users;
};

/*
 * This function returns a pointer to the struct group with the name
 * @group_name.
 * On success a pointer to the struct group is returned , otherwise NULL is
 * returned indicating that the group could not be found and therefore does not
 * exist.
 * @group_name:	char * containing the group_name to look for in the group
 * database.
 */
struct group * get_group(char *group_name);

#endif
