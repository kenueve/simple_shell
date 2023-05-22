#include "shell.h"

/**
 * list_len - calculates the length
 *  of a linked list.
 * @f: ptr to first node.
 *
 * Return: list's size.
 */
size_t list_len(const list_t *f)
{
	size_t l = 0;

	while (f)
	{
		f = f->next;
		l++;
	}
	return (l);
}

/**
 * list_to_strings converts a linked list of
 *  type list_t into an array of strings.
 * @_hd: ptr to first node
 *
 * Return: array of the strngs
 */
char **list_to_strings(list_t *_hd)
{
	list_t *ndee = _hd;
	size_t l = list_len(_hd), j;
	char **stri;
	char *str;

	if (!_hd || !l)
		return (NULL);
	stri = malloc(sizeof(char *) * (l + 1));
	if (!stri)
		return (NULL);
	for (l = 0; ndee; ndee = ndee->next, l++)
	{
		str = malloc(_strlen(ndee->str) + 1);
		if (!str)
		{
			for (j = 0; j < l; j++)
				free(stri[j]);
			free(stri);
			return (NULL);
		}

		str = _strcpy(str, ndee->str);
		stri[l] = str;
	}
	stri[l] = NULL;
	return (stri);
}


/**
 * print_list - displays all elements
 *  of a linked list of type list_t.
 * @f: ptr to the first node
 *
 * Return: list's size
 */
size_t print_list(const list_t *f)
{
	size_t l = 0;

	while (f)
	{
		_puts(convert_number(f->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(f->str ? f->str : "(nil)");
		_puts("\n");
		f = f->next;
		l++;
	}
	return (l);
}

/**
 * node_starts_with - returns the node in the
 *  linked list whose string starts
 *  with the specified prefix.
 * @ndee: ptr to the head list.
 * @prefix: string to be matched
 *  as a prefix.
 * @c:  next char after the prefix
 *  to be matched
 * Return: match node or null
 */
list_t *node_starts_with(list_t *ndee, char *prefix, char c)
{
	char *p = NULL;

	while (ndee)
	{
		p = starts_with(ndee->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (ndee);
		ndee = ndee->next;
	}
	return (NULL);
}

/**
 * get_node_index - retrieves the index of
 *  a node in a linked list.
 * @_hd: ptr to head of the list.
 * @ndee: ptr to the node.
 *
 * Return: -1
 * or index of node.
 */

ssize_t get_node_index(list_t *_hd, list_t *ndee)
{
	size_t l = 0;

	while (_hd)
	{
		if (_hd == ndee)
			return (l);
		_hd = _hd->next;
		l++;
	}
	return (-1);
}

