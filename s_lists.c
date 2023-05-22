#include "shell.h"

/**
 * add_node - inserts a new node at
 *  the beginning of the list.
 * @hed: address of the ptr
 *  to the head node.
 * @str: field of node's structure.
 * @num: index of the node
 *  used by history.
 * Return: list size.
 */
list_t *add_node(list_t **hed, const char *str, int num)
{
	list_t *nhed;

	if (!hed)
		return (NULL);
	nhed = malloc(sizeof(list_t));
	if (!nhed)
		return (NULL);
	_memset((void *)nhed, 0, sizeof(list_t));
	nhed->num = num;
	if (str)
	{
		nhed->str = _strdup(str);
		if (!nhed->str)
		{
			free(nhed);
			return (NULL);
		}
	}
	nhed->next = *hed;
	*hed = nhed;
	return (nhed);
}

/**
 * add_node_end - appends a new node at the lists end.
 * @hed: address of the ptr
 *  to the head node.
 * @str: node field string.
 * @num: index of the node used by history.
 *
 * Return: list'ss size.
 */
list_t *add_node_end(list_t **hed, const char *str, int num)
{
	list_t *n_node, *ndee;

	if (!hed)
		return (NULL);

	ndee = *hed;
	n_node = malloc(sizeof(list_t));
	if (!n_node)
		return (NULL);
	_memset((void *)n_node, 0, sizeof(list_t));
	n_node->num = num;
	if (str)
	{
		n_node->str = _strdup(str);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (ndee)
	{
		while (ndee->next)
			ndee = ndee->next;
		ndee->next = n_node;
	}
	else
		*hed = n_node;
	return (n_node);
}

/**
 * print_list_str - displays only the 'str'
 * element of a linked list of type list_t.
 * @f: ptr to the first node of the list.
 * Return: list size.
 */
size_t print_list_str(const list_t *f)
{
	size_t t = 0;

	while (f)
	{
		_puts(f->str ? f->str : "(nil)");
		_puts("\n");
		f = f->next;
		t++;
	}
	return (t);
}

/**
 * delete_node_at_index - emoves a node at
 *  the specified index.
 * @hed: ptr address to the first node.
 * @index: node indx to be deleted.
 *
 * Return: if it succeed 1
 *   if other 0.
 */
int delete_node_at_index(list_t **hed, unsigned int index)
{
	list_t *ndee, *prev_node;
	unsigned int t = 0;

	if (!hed || !*hed)
		return (0);

	if (!index)
	{
		ndee = *hed;
		*hed = (*hed)->next;
		free(ndee->str);
		free(ndee);
		return (1);
	}
	ndee = *hed;
	while (ndee)
	{
		if (t == index)
		{
			prev_node->next = ndee->next;
			free(ndee->str);
			free(ndee);
			return (1);
		}
		t++;
		prev_node = ndee;
		ndee = ndee->next;
	}
	return (0);
}

/**
 * free_list - releases memory occupied
 *  by all nodes of a linked list.
 * @head_ptr: ptr address to the head node.
 *
 * Return: null
 */
void free_list(list_t **head_ptr)
{
	list_t *ndee, *next_node, *hed;

	if (!head_ptr || !*head_ptr)
		return;
	hed = *head_ptr;
	ndee = hed;
	while (ndee)
	{
		next_node = ndee->next;
		free(ndee->str);
		free(ndee);
		ndee = next_node;
	}
	*head_ptr = NULL;
}

