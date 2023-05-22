#include "shell.h"

/**
 * _erratoi - changes string to int
 * @strng: string to be changed.
 * Return: if no nums in string return 0
 *   if other converted number
 *   if error occurs -1
 */
int _erratoi(char *strng)
{
	int a = 0;
	unsigned long int rslt = 0;

	if (*strng == '+')
		strng++;
	for (a = 0;  strng[a] != '\0'; a++)
	{
		if (strng[a] >= '0' && strng[a] <= '9')
		{
			rslt *= 10;
			rslt += (strng[a] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
}

/**
 * print_error - it prints error msgs.
 * @inff: parameter and inff struct return.
 * @erstring: a specified error string.
 * Return: if no nums in string return 0
 *   if othere convert number
 *   if error occurs -1
 */
void print_error(info_t *inff, char *erstring)
{
	_eputs(inff->fname);
	_eputs(": ");
	print_d(inff->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inff->argv[0]);
	_eputs(": ");
	_eputs(erstring);
}

/**
 * print_d - it prints decimal nums (integer)
 * @inpt: input
 * @filedes: filedescriptor to bewritten in.
 *
 * Return: numb of chars printed
 */
int print_d(int inpt, int filedes)
{
	int (*__putchar)(char) = _putchar;
	int a, cnt = 0;
	unsigned int abs, cur;

	if (filedes == STDERR_FILENO)
		__putchar = _eputchar;
	if (inpt < 0)
	{
		abs = -inpt;
		__putchar('-');
		cnt++;
	}
	else
		abs = inpt;
	cur = abs;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (abs / a)
		{
			__putchar('0' + cur / a);
			cnt++;
		}
		cur %= a;
	}
	__putchar('0' + cur);
	cnt++;

	return (cnt);
}

/**
 * convert_number - it converts functions.
 * @numb: the number
 * @bs: the base
 * @flg: args flags
 *
 * Return: string
 */
char *convert_number(long int numb, int bs, int flg)
{
	static char *arr;
	static char buf[50];
	char sg = 0;
	char *pointer;
	unsigned long n = numb;

	if (!(flg & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sg = '-';

	}
	arr = flg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buf[49];
	*pointer = '\0';

	do	{
		*--pointer = arr[n % bs];
		n /= bs;
	} while (n != 0);

	if (sg)
		*--pointer = sg;
	return (pointer);
}

/**
 * remove_comments -it replace the first
 * instance of # with '\0'
 * @buf: string adress
 *
 * Return: 0
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}

