#include "shell.h"

/**
 * get_history_file - shows file containing
 * histry
 * @inff: structure parameter
 *
 * Return: A dynamically allocated
 * string containing the histry file.
 */

char *get_history_file(info_t *inff)
{
	char *bff, *drt;

	drt = _getenv(inff, "HOME=");
	if (!drt)
		return (NULL);
	bff = malloc(sizeof(char) * (_strlen(drt) + _strlen(HIST_FILE) + 2));
	if (!bff)
		return (NULL);
	bff[0] = 0;
	_strcpy(bff, drt);
	_strcat(bff, "/");
	_strcat(bff, HIST_FILE);
	return (bff);
}

/**
 * write_history - generates a new file
 * or appends to an existing file.
 * @inff: structure paramter
 *
 * Return: if it succeed 1
 *  if other -1.
 */
int write_history(info_t *inff)
{
	ssize_t fud;
	char *filename = get_history_file(inff);
	list_t *nde = NULL;

	if (!filename)
		return (-1);

	fud = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fud == -1)
		return (-1);
	for (nde = inff->history; nde; nde = nde->next)
	{
		_putsfd(nde->str, fud);
		_putfd('\n', fud);
	}
	_putfd(BUF_FLUSH, fud);
	close(fud);
	return (1);
}

/**
 * read_history - it reads from the histpry file.
 * @inff: structure paramter
 *
 * Return: count histry when success,
 *  if other return 0
 */
int read_history(info_t *inff)
{
	int i, lst = 0, countlin = 0;
	ssize_t fud, readln, fusize = 0;
	struct stat st;
	char *bff = NULL, *filename = get_history_file(inff);

	if (!filename)
		return (0);

	fud = open(filename, O_RDONLY);
	free(filename);
	if (fud == -1)
		return (0);
	if (!fstat(fud, &st))
		fusize = st.st_size;
	if (fusize < 2)
		return (0);
	bff = malloc(sizeof(char) * (fusize + 1));
	if (!bff)
		return (0);
	readln = read(fud, bff, fusize);
	bff[fusize] = 0;
	if (readln <= 0)
		return (free(bff), 0);
	close(fud);
	for (i = 0; i < fusize; i++)
		if (bff[i] == '\n')
		{
			bff[i] = 0;
			build_history_list(inff, bff + lst, countlin++);
			lst = i + 1;
		}
	if (lst != i)
		build_history_list(inff, bff + lst, countlin++);
	free(bff);
	inff->histcount = countlin;
	while (inff->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inff->history), 0);
	renumber_history(inff);
	return (inff->histcount);
}

/**
 * build_history_list - appends an entry to
 *  a linked list representing the histry.
 * @inff: structure containing
 *  relevant args for maintenance.
 * @bff: bff
 * @countlin: the line count representing
 *  the histry (histcount).
 * Return: 0
 */
int build_history_list(info_t *inff, char *bff, int countlin)
{
	list_t *nde = NULL;

	if (inff->history)
		nde = inff->history;
	add_node_end(&nde, bff, countlin);

	if (!inff->history)
		inff->history = nde;
	return (0);
}

/**
 * renumber_history - updates the histry linked list
 *  numbering after changes.
 * @inff: structure holding potential
 *  args for maintenance.
 * Return: the new histcount
 */
int renumber_history(info_t *inff)
{
	list_t *nde = inff->history;
	int i = 0;

	while (nde)
	{
		nde->num = i++;
		nde = nde->next;
	}
	return (inff->histcount = i);
}

