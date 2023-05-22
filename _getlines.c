#include "shell.h"

/**
 * input_buf - buf chained cmds.
 * @inff: structure parameter
 * @bff: buf address
 * @lg: length variable address.
 *
 * Return: the bytes read
 */
ssize_t input_buf(info_t *inff, char **bff, size_t *lg)
{
	ssize_t e = 0;
	size_t lng_p = 0;

	if (!*lg)
	{

		free(*bff);
		*bff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		e = getline(bff, &lng_p, stdin);
#else
		e = _getline(inff, bff, &lng_p);
#endif
		if (e > 0)
		{
			if ((*bff)[e - 1] == '\n')
			{
				(*bff)[e - 1] = '\0';
				e--;
			}
			inff->linecount_flag = 1;
			remove_comments(*bff);
			build_history_list(inff, *bff, inff->histcount++);

			{
				*lg = e;
				inff->cmd_buf = bff;
			}
		}
	}
	return (e);
}

/**
 * get_input - chekcs a line - newline
 * @inff: structure parameter
 *
 * Return: the bytes read
 */
ssize_t get_input(info_t *inff)
{
	static char *bff;
	static size_t t, m, lg;
	ssize_t e = 0;
	char **buf_p = &(inff->arg), *pointer;

	_putchar(BUF_FLUSH);
	e = input_buf(inff, &bff, &lg);
	if (e == -1)
		return (-1);
	if (lg)
	{
		m = t;
		pointer = bff + t;

		check_chain(inff, bff, &m, t, lg);
		while (m < lg)
		{
			if (is_chain(inff, bff, &m))
				break;
			m++;
		}

		t = m + 1;
		if (t >= lg)
		{
			t = lg = 0;
			inff->cmd_buf_type = CMD_NORM;
		}

		*buf_p = pointer;
		return (_strlen(pointer));
	}

	*buf_p = bff;
	return (e);
}

/**
 * read_buf - it read the buf
 * @inff: structure parameter
 * @bff: buf
 * @t: the size
 *
 * Return: e
 */
ssize_t read_buf(info_t *inff, char *bff, size_t *t)
{
	ssize_t e = 0;

	if (*t)
		return (0);
	e = read(inff->readfd, bff, READ_BUF_SIZE);
	if (e >= 0)
		*t = e;
	return (e);
}

/**
 * _getline - checks the upcoming input line
 * from STDIN
 * @inff: structure parameter.
 * @ptr: address of ptr to buf
 *  NULL or preallocated.
 * @length: size of ptr buf
 *  if not NULL
 *
 * Return: s
 */
int _getline(info_t *inff, char **ptr, size_t *length)
{
	static char bff[READ_BUF_SIZE];
	static size_t t, lg;
	size_t k;
	ssize_t e = 0, s = 0;
	char *pointer = NULL, *new_p = NULL, *c;

	pointer = *ptr;
	if (pointer && length)
		s = *length;
	if (t == lg)
		t = lg = 0;

	e = read_buf(inff, bff, &lg);
	if (e == -1 || (e == 0 && lg == 0))
		return (-1);

	c = _strchr(bff + t, '\n');
	k = c ? 1 + (unsigned int)(c - bff) : lg;
	new_p = _realloc(pointer, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (pointer ? free(pointer), -1 : -1);

	if (s)
		_strncat(new_p, bff + t, k - t);
	else
		_strncpy(new_p, bff + t, k - t + 1);

	s += k - t;
	t = k;
	pointer = new_p;

	if (length)
		*length = s;
	*ptr = pointer;
	return (s);
}

/**
 * sigintHandler - it block [ctrl-C].
 * @sig_num: num signal.
 *
 * Return: null
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

