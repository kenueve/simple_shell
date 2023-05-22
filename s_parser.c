#include "shell.h"

/**
 * is_cmd - determines whether a file
 *  is an executable cmd.
 * @inff: structure inff.
 * @pth: file's path.
 * Return: true = 1
 *  other = 0
 */
int is_cmd(info_t *inff, char *pth)
{
	struct stat stru;

	(void)inff;
	if (!pth || stat(pth, &stru))
		return (0);

	if (stru.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - creates a duplicate of chars
 *  within a specified range.
 * @strpth: string's path.
 * @strt: index's strating.
 * @stp: index's stopping
 * Return: ptr to new buf
 */
char *dup_chars(char *strpth, int strt, int stp)
{
	static char buf[1024];
	int l = 0, j = 0;

	for (j = 0, l = strt; l < stp; l++)
		if (strpth[l] != ':')
			buf[j++] = strpth[l];
	buf[j] = 0;
	return (buf);
}

/**
 * find_path - searches for the given
 *  cmd in the path string.
 * @inff: structure inff.
 * @strpth: string's path.
 * @cmnd: command to be found.
 *
 * Return: command path if it is found
 *  or void
 */
char *find_path(info_t *inff, char *strpth, char *cmnd)
{
	int l = 0, curr_pos = 0;
	char *pth;

	if (!strpth)
		return (NULL);
	if ((_strlen(cmnd) > 2) && starts_with(cmnd, "./"))
	{
		if (is_cmd(inff, cmnd))
			return (cmnd);
	}
	while (1)
	{
		if (!strpth[l] || strpth[l] == ':')
		{
			pth = dup_chars(strpth, curr_pos, l);
			if (!*pth)
				_strcat(pth, cmnd);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, cmnd);
			}
			if (is_cmd(inff, pth))
				return (pth);
			if (!strpth[l])
				break;
			curr_pos = l;
		}
		l++;
	}
	return (NULL);
}

