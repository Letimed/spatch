#ifndef LIST_H
#define LIST_H

/*
 * Generic linked list for data storage
 * @next:	pointer to the next list_head
 * @prev:	pointer to the previous list_head
 */
struct list_head
{
	struct list_head *next;
	struct list_head *prev;
};

/* Initialize a struct list_head */
#define LIST_HEAD_INIT(name) { &(name), &(name) }

/* Initialize a struct list_head * */
#define INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

/* Create and initialize a struct list_head */
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

/* Compute the adress of the containing struct from the adress of the struct
 * list_head that it contains
 * @ptr:	pointer to a struct list_head
 * @type:	type of the containing struct
 * @member:	name of the struct list_head in the containing struct
 */
#define LIST_ENTRY(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

/*
 * iterate over a list safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop counter.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define LIST_FOR_EACH(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)
/*
 * Add a struct list_head to the list
 * @new:	pointer to the struct list_head to add
 * @head:	pointer to the head of the list
 */
void list_add(struct list_head *new, struct list_head *head);

/*
 * Add a struct list_head at the back of the list
 * @new:	pointer to the struct list_head to add
 * @head:	pointer to the head of the list
 */
void list_add_back(struct list_head *new, struct list_head *head);

void __list_add(struct list_head *new,
		struct list_head *prev,
		struct list_head *next);

/*
 * Delete a struct list_head from the list
 * @entry:	pointer to the struct list_head to delete
 */
void list_del(struct list_head *entry);

void __list_del(struct list_head *prev, struct list_head *next);

/*
 * Compute the size of the list
 * @head:	pointer to the head of the list
 */
int list_size(struct list_head *head);

#endif
