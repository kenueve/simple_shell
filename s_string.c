#include "shell.h"

/**
 * _strlen - computes the string's length.
 * @st: string to calculate the length of.
 *
 * Return:  length of the string as an int.
 */
int _strlen(char *st)
{
	int l = 0;

	if (!st)
		return (0);

	while (*st++)
		l++;
	return (l);
}

/**
 * _strcmp - compares 2 strings lexicographically.
 * @str_one: string 1
 * @str_two: string 2
 *
 * Return: negative value if str_one < str_two
 *   positive value if str_one > str_two
 *   0 if str_one == str_two.
 */
int _strcmp(char *str_one, char *str_two)
{
	while (*str_one && *str_two)
	{
		if (*str_one != *str_two)
			return (*str_one - *str_two);
		str_one++;
		str_two++;
	}
	if (*str_one == *str_two)
		return (0);
	else
		return (*str_one < *str_two ? -1 : 1);
}

/**
 * starts_with - checks if the string 'ndl'
 *  starts with the string 'hstck'.
 * @hstck: strng to besearched.
 * @ndl: substring to be found
 * Return: address of the next char of
 *  'hstck' if found,
 *   otherwise = void .
 */
char *starts_with(const char *hstck, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *hstck++)
			return (NULL);
	return ((char *)hstck);
}

/**
 * _strcat - concatentes 2 string.
 * @destination:  dest buf
 * @source: src buf
 *
 * Return: ptr to destination buf.
 */
char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}

