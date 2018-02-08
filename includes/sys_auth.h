#ifndef SYS_AUTH_H
#define SYS_AUTH_H

#include <security/pam_appl.h>

/*
 * Global pam_response , this variable is used in the function
 * function_conversation.
 */
struct pam_response *reply;

/*
 * This function is used to handle the conversation between PAM and spatch.
 * It's behavious is very simple , it just copy the reply in *(@resp)
 * @num_msg:	message number
 * @msg:	pam message
 * @resp:	response of pam
 * @data:	user defined pointer (unused here)
 */
int function_conversation(int num_msg, const struct pam_message **msg,
			  struct pam_response **resp, void *data);

/*
 * This function calls pam and validate the username / password couple thanks to 
 * the function function_conversation. This function returns 0 or 1 wether the
 * provided couple is valid.
 * @username:	username
 * @password:	password
 */
int system_authentification(const char *username, const char *password);

#endif
