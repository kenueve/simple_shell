#include "shell.h"

/**
 * **strtow - splits a string into words,
 * ignoring repeated delimiters.
 * @strg: string
 * @deli: delim string
 * Return: in case of success return a ptr to an
 * array of strings,
 *  in case of failure return void
 */
char **strtow(char *strg, char *deli)
{
	int l, h, f, n, numofwords = 0;
	char **stt;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	if (!deli)
		deli = " ";
	for (l = 0; strg[l] != '\0'; l++)
		if (!is_delim(strg[l], deli) && (is_delim(strg[l + 1], deli) || !strg[l + 1]))
			numofwords++;

	if (numofwords == 0)
		return (NULL);
	stt = malloc((1 + numofwords) * sizeof(char *));
	if (!stt)
		return (NULL);
	for (l = 0, h = 0; h < numofwords; h++)
	{
		while (is_delim(strg[l], deli))
			l++;
		f = 0;
		while (!is_delim(strg[l + f], deli) && strg[l + f])
			f++;
		stt[h] = malloc((f + 1) * sizeof(char));
		if (!stt[h])
		{
			for (f = 0; f < h; f++)
				free(stt[f]);
			free(stt);
			return (NULL);
		}
		for (n = 0; n < f; n++)
			stt[h][n] = strg[l++];
		stt[h][n] = 0;
	}
	stt[h] = NULL;
	return (stt);
}

/**
 * **strtow2 - separates a string into
 * words based on a delimiter.
 * @strg: string
 * @deli: delim string
 * Return: in case of success return a ptr to an
 * array of strings,
 *  in case of failure return void
 */
char **strtow2(char *strg, char deli)
{
	int l, h, f, n, numofwords = 0;
	char **stt;

	if (strg == NULL || strg[0] == 0)
		return (NULL);
	for (l = 0; strg[l] != '\0'; l++)
		if ((strg[l] != deli && strg[l + 1] == deli) ||
		    (strg[l] != deli && !strg[l + 1]) || strg[l + 1] == deli)
			numofwords++;
	if (numofwords == 0)
		return (NULL);
	stt = malloc((1 + numofwords) * sizeof(char *));
	if (!stt)
		return (NULL);
	for (l = 0, h = 0; h < numofwords; h++)
	{
		while (strg[l] == deli && strg[l] != deli)
			l++;
		f = 0;
		while (strg[l + f] != deli && strg[l + f] && strg[l + f] != deli)
			f++;
		stt[h] = malloc((f + 1) * sizeof(char));
		if (!stt[h])
		{
			for (f = 0; f < h; f++)
				free(stt[f]);
			free(stt);
			return (NULL);
		}
		for (n = 0; n < f; n++)
			stt[h][n] = strg[l++];
		stt[h][n] = 0;
	}
	stt[h] = NULL;
	return (stt);
}

