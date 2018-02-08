#ifndef ENDPOINT_H
#define ENDPOINT_H

#include "config.h"
#include "list.h"

#define HOSTNAME	"Hostname"
#define USERNAME	"Username"
#define PASSWORD	"Password"
#define PORT		"Port"
#define ALLOWED_USERS	"Allowed_users"

/*
 * Structure representing an endpoint :
 * @hostname:	hostname of the endpoint
 * @username:	default username
 * @password:	default password
 * @port:	default port to connect to
 * @allowed_users: list of allowed users on the endpoint
 * @denied_users: list of denied users on the endpoint
 * @allowed_groups: list of allowed groups on the endpoint
 * @endpoints:	link to other endpoints
 */
struct endpoint
{
	char	*hostname;
	char	*username;
	char	*password;
	int	port;

	struct list_head allowed_users;
	struct list_head denied_users;
	struct list_head allowed_groups;
	struct list_head endpoints;
};

/*
 * Iterates over all files in the directory pointed by path and for each file
 * fill a struct endpoint if possible by aclling parse_endpoint on it.
 * This function will automaticaly remove every invalid endpoint and return
 * the number of invalid endpoints.
 * The endpoints will be linked together by the struct list_head given.
 * @head:	preallocated head of the endpoint linked list
 * @path:	directory to load the endpoints from
 */
int load_endpoints(struct list_head *head, const char *path);

/*
 * Parse the file pointed by @path and fill the @edp structure accordingly.
 * On error this function will return a non zero positive value.
 * On success this function will return zero.
 * @edp:	pointer to the previously allocated struct endpoint
 * @path:	path to the file to parse.
 */
int parse_endpoint(struct endpoint *edp, const char *path);

/*
 * Parse a line and dispatch the tokens to the correct handler.
 * return 0 on success -1 on failure.
 * @edp:	endpoint to fill
 * @line:	string to extract the data from
 */
int parse_line(struct endpoint *edp, char *line);

/*
 * Iterate over the given struct list_head and call __delete_endpoint
 * on each node. Then removes the node from the list and goes to the next one.
 * This function will ERASE every data contained in the list !
 * @head:	struct list_head being the endpoints list
 */
int delete_endpoints(struct list_head *head);

/*
 * Delete the attributes of the given struct endpoint by freeing them if
 * necessary. The actual @edp ptr is not freed , it is up to the caller to do
 * it.
 * @edp:	actual endpoint to delete
 */
int __delete_endpoint(struct endpoint *edp);


/* Parse and set an hostname in the given struct endpoint from the given string
 * this function returns 0 on success , any non zero value otherwise.
 * @edp:	struct endpoint to set the hostname
 * @token:	char * where to look for the hostname
 */
int parse_hostname(struct endpoint *edp, const char *token);

/*
 * Parse and set a username in the given struct endpoint from the given string.
 * this function returns 0 on success , any non zero value otherwise.
 * @edp:	struct endpoint to set the username
 * @token:	char * where to look for the username
 */
int parse_username(struct endpoint *edp, const char *token);

/*
 * Parse and set a password in the given struct endpoint from the given string.
 * this function returns 0 on success , any non zero value otherwise.
 * @edp:	struct endpoint to set the password
 * @token:	char * where to look for the password
 */
int parse_password(struct endpoint *edp, const char *token);

/*
 * Parse and set the connection port for the given struct endpoint from the
 * given string.
 * This function return 0 on success , any non zero value otherwise.
 * @edp:	struct endpoint to set the port
 * @token:	char * where to look for the port
 */
int parse_port(struct endpoint *edp, const char *token);

/*
 * Parse and set the allowed users for the given struct endpoint.
 * This function will fill the allowed_users linked list embedded in the struct
 * endpoint with every allowed user found in token.
 * This function return 0 on success , any non zero value otherwise.
 * @edp:	struct endpoint to set the allowed_users
 * @token:	char * where to look for the allowedusers
 */
int parse_allowed_users(struct endpoint *edp, char *token);

/*
 * Parse and set the denied users for the given struct endpoint.
 * This function will fill the denied_users linked list embedded in the struct
 * endpoint with every denied user found in token.
 * This function return 0 on success , any non zero value otherwise.
 * @edp:	struct endpoint to set the denied users
 * @tokan:	char * where to find the denied users.
 */
int parse_denied_users(struct endpoint *edp, char *token);

/*
 * Parse and set the allowed groups in for the given struct endpoint.
 * This function will fill the allowed_groups linked list embedded in the struct
 * endpoint with every allowed groups found in token.
 * This function return 0 on success , any non zero value otherwise.
 * @edp:	struct endpoint to set the allowed groups
 * @token:	char * where to look for the allowed groups
 */
int parse_allowed_groups(struct endpoint *edp, char *token);

#endif
