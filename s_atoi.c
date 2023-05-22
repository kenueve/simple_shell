#include "shell.h"

/**
 * interactive - when shell is in
 * nteractive mode it returns true
 * @inff: adress of strct
 *
 * Return: if interactive modeis active return 1
 * if other return zero
 */
int interactive(info_t *inff)
{
	return (isatty(STDIN_FILENO) && inff->readfd <= 2);
}

/**
 * is_delim - it tests if the dlm is a char
 * @s: character
 * @dlm: dlm
 * Return: true = 1
 *  other = 0
 */
int is_delim(char s, char *dlm)
{
	while (*dlm)
		if (*dlm++ == s)
			return (1);
	return (0);
}

/**
 *_isalpha - looks for alphabetic char
 *@s: character
 *Return: if character is alphab = 1
  other = 0
 */

int _isalpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - turns string to int
 *@s: string
 *Return: if there's no string return 0
  if other convert num
 */

int _atoi(char *s)
{
	int n, flsh = 1, flg = 0, utp;
	unsigned int result = 0;

	for (n = 0;  s[n] != '\0' && flg != 2; n++)
	{
		if (s[n] == '-')
			flsh *= -1;

		if (s[n] >= '0' && s[n] <= '9')
		{
			flg = 1;
			result *= 10;
			result += (s[n] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (flsh == -1)
		utp = -result;
	else
		utp = result;

	return (utp);
}
