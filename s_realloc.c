#include "shell.h"

/**
 **_memset - fills a memory area with
 * a constant byte.
 *@r: pointer to memory area.
 *@y: byte to fill memory area with.
 *@nu: num of bytes to be filled.
 *Return: pointer to the memory area 'r'.
 */
char *_memset(char *r, char y, unsigned int nu)
{
	unsigned int o;

	for (o = 0; o < nu; o++)
		r[o] = y;
	return (r);
}

/**
 * ffree - frees the memory allocated
 *  for a string of strings
 * @ps: pointer to the string of strings.
 */
void ffree(char **ps)
{
	char **a = ps;

	if (!ps)
		return;
	while (*ps)
		free(*ps++);
	free(a);
}

/**
 * _realloc - adjusts the size of a
 *  previously allocated block of memory.
 * @pointer: pointer to the previously allocated block.
 * @o_size: size of the previous block in bytes.
 * @n_size: size of the new block in bytes.
 * Return: pointer to the reallocated
 *  block of memory.
 */
void *_realloc(void *pointer, unsigned int o_size, unsigned int n_size)
{
	char *p;

	if (!pointer)
		return (malloc(n_size));
	if (!n_size)
		return (free(pointer), NULL);
	if (n_size == o_size)
		return (pointer);

	p = malloc(n_size);
	if (!p)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		p[o_size] = ((char *)pointer)[o_size];
	free(pointer);
	return (p);
}

