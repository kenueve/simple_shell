#include "shell.h"

/**
 * bfree - frees a pointer and sets
 *  the address to NULL.
 * @pointer: address of the pointer to be freed.
 *
 * Return: if it's freed return 1
 *  if other return 0.
 */

int bfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

