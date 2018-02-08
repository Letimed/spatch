#include <stdlib.h>
#include <errno.h>
#include "list.h"

void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}

void list_add_back(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

void __list_add(struct list_head *new,
		       struct list_head *prev,
		       struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}


void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = NULL;
	entry->prev = NULL;
}

void __list_del(struct list_head *prev, struct list_head *next)
{
	prev->next = next;
	next->prev = prev;
}

int list_size(struct list_head *head)
{
	int size;
	struct list_head *pos;
	struct list_head *n;

	size = 0;

	LIST_FOR_EACH(pos, n, head)
		size = size + 1;

	return size;
}
