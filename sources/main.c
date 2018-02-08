#include "list.h"
#include "endpoint.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>

struct test_list {
    struct list_head list;
    int data;
};

int main(int argc, char const* argv[])
{
	struct list_head head;

	INIT_LIST_HEAD(&head);

	load_endpoints(&head, "../test/endpoints");

	struct list_head *pos;
	struct list_head *n;

	struct list_head *u_pos;
	struct list_head *u_n;

	LIST_FOR_EACH(pos, n, &head)
	{
		struct endpoint *edp;

		edp = LIST_ENTRY(pos, struct endpoint, endpoints);

		printf("Hostname : %s\n", edp->hostname);
		printf("Username : %s\n", edp->username);
		printf("Password : %s\n", edp->password);
		printf("Port : %d\n", edp->port);
		printf("Allowed users : ");

		LIST_FOR_EACH(u_pos, u_n, &edp->allowed_users)
		{
			struct user *usr;

			usr = LIST_ENTRY(u_pos, struct user, users);
			printf("%s,", usr->username);
		}
		printf("\n\n\n");
	}

	delete_endpoints(&head);

	printf("The list is now : %d long\n", list_size(&head));

	return 0;
}
