#include "shell.h"

/**
 * clear_info - starts the structure of info_t
 * @inff: structure address
 */
void clear_info(info_t *inff)
{
	inff->arg = NULL;
	inff->argv = NULL;
	inff->path = NULL;
	inff->argc = 0;
}

/**
 * set_info - starts the structure of info_t
 * @inff: structure address
 * @argv: arg vector
 */
void set_info(info_t *inff, char **argv)
{
	int l = 0;

	inff->fname = argv[0];
	if (inff->arg)
	{
		inff->argv = strtow(inff->arg, " \t");
		if (!inff->argv)
		{

			inff->argv = malloc(sizeof(char *) * 2);
			if (inff->argv)
			{
				inff->argv[0] = _strdup(inff->arg);
				inff->argv[1] = NULL;
			}
		}
		for (l = 0; inff->argv && inff->argv[l]; l++)
			;
		inff->argc = l;

		replace_alias(inff);
		replace_vars(inff);
	}
}

/**
 * free_info - it frees the field of
 * info_t struct
 * @inff: structure address
 * @alfields: it is valid if its
 * freeing alfields fields
 */
void free_info(info_t *inff, int alfields)
{
	ffree(inff->argv);
	inff->argv = NULL;
	inff->path = NULL;
	if (alfields)
	{
		if (!inff->cmd_buf)
			free(inff->arg);
		if (inff->env)
			free_list(&(inff->env));
		if (inff->history)
			free_list(&(inff->history));
		if (inff->alias)
			free_list(&(inff->alias));
		ffree(inff->environ);
			inff->environ = NULL;
		bfree((void **)inff->cmd_buf);
		if (inff->readfd > 2)
			close(inff->readfd);
		_putchar(BUF_FLUSH);
	}
}

