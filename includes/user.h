#ifndef USER_H
#define USER_H

#include "config.h"
#include "list.h"

/*
 * Structure representing a user :
 * @username:	name of the user
 * @password:	password of the user
 * @users:	link to the other users
 * @groups:	link to the groups the user belongs to
 */
struct user
{
	char *username;
	char *password;
	struct list_head users;
	struct list_head groups;
};

/*
 * This function return a pointer to the struct user containing the username asked for in
 * @username.
 * On success a pointer to the struct user is returned , otherwise NULL is
 * returned indicating that the user could not be found and therefore does not
 * exist.
 * @username:	char * containing the username to look for in the user database.
 */
struct user * get_user(char *username);

#endif
