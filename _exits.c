#include "shell.h"

/**
 **_strncpy - cp the string
 *@dest: string destination.
 *@src: original string
 *@n: num of chars to be cpied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int b, k;
	char *s = dest;

	b = 0;
	while (src[b] != '\0' && b < n - 1)
	{
		dest[b] = src[b];
		b++;
	}
	if (b < n)
	{
		k = b;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 **_strncat - concatentes 2 strings
 *@dest: string 1
 *@src: string 2
 *@n: num of bytes to be used
 *Return: concatented string
 */
char *_strncat(char *dest, char *src, int n)
{
	int b, k;
	char *s = dest;

	b = 0;
	k = 0;
	while (dest[b] != '\0')
		b++;
	while (src[k] != '\0' && k < n)
	{
		dest[b] = src[k];
		b++;
		k++;
	}
	if (k < n)
		dest[b] = '\0';
	return (s);
}

/**
 **_strchr - finds char in a string
 *@s: string.
 *@c: character.
 *Return: ptr (s) to memory area s.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

