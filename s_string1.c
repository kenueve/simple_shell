#include "shell.h"

/**
 * _strcpy - cp the string
 * @destination: string dest
 * @source: string src
 *
 * Return: ptr to dest
 */
char *_strcpy(char *destination, char *source)
{
	int l = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[l])
	{
		destination[l] = source[l];
		l++;
	}
	destination[l] = 0;
	return (destination);
}

/**
 * _strdup - doubles the string
 * @string: string to be doubled
 * Return: ptr to the doubled strng.
 */
char *_strdup(const char *string)
{
	int len = 0;
	char *_ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		len++;
	_ret = malloc(sizeof(char) * (len + 1));
	if (!_ret)
		return (NULL);
	for (len++; len--;)
		_ret[len] = *--string;
	return (_ret);
}

/**
 *_puts - prints a string.
 *@string: string to be printd
 *
 * Return: void
 */
void _puts(char *string)
{
	int l = 0;

	if (!string)
		return;
	while (string[l] != '\0')
	{
		_putchar(string[l]);
		l++;
	}
}

/**
 * _putchar - writes char to stdout.
 * @c: char to be printed.
 *
 * Return: 1 if it succeed.
 *  -1 if error occurs
 *  errno is set appropriately.
 */
int _putchar(char c)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(1, buf, l);
		l = 0;
	}
	if (c != BUF_FLUSH)
		buf[l++] = c;
	return (1);
}

