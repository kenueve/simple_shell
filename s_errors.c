#include "shell.h"

/**
 *_eputs - it print inpt string
 * @string: string.
 *
 * Return: NULL
 */
void _eputs(char *string)
{
	int v = 0;

	if (!string)
		return;
	while (string[v] != '\0')
	{
		_eputchar(string[v]);
		v++;
	}
}

/**
 * _eputchar - writes the character 'charr'
 *  to the standard error stream (stderr).
 * @charr: character
 *
 * Return: 1 if succed.
 * -1 if other.
 */
int _eputchar(char charr)
{
	static int v;
	static char buffer[WRITE_BUF_SIZE];

	if (charr == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(2, buffer, v);
		v = 0;
	}
	if (charr != BUF_FLUSH)
		buffer[v++] = charr;
	return (1);
}

/**
 * _putfd - writes the character 'charr'
 *  to the specified file descriptor (fileds).
 * @charr: char to be written.
 * @fileds: file descriptor to which the
 *  character will be written
 * Return: 1 if it succed .
 * -1 if other.
 **/
int _putfd(char charr, int fileds)
{
	static int v;
	static char buffer[WRITE_BUF_SIZE];

	if (charr == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(fileds, buffer, v);
		v = 0;
	}
	if (charr != BUF_FLUSH)
		buffer[v++] = charr;
	return (1);
}

/**
 *_putsfd - wirtes input string
 * @string: string to be written.
 * @fileds: file descriptor to which the
 *  character will be written.
 * Return: number of chars.
 */

int _putsfd(char *string, int fileds)
{
	int v = 0;

	if (!string)
		return (0);
	while (*string)
	{
		v += _putfd(*string++, fileds);
	}
	return (v);
}

