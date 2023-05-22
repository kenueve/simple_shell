#include "shell.h"

/**
 * is_chain - checks if the current char in
 * the buf is a chain delimiter.
 * @inff: structure parameter.
 * @bff: char buuff.
 * @g: ddress of the current position in buf.
 *
 * Return: if chain delimeter return 1,
 *  if other 0
 */
int is_chain(info_t *inff, char *bff, size_t *g)
{
	size_t j = *g;

	if (bff[j] == '|' && bff[j + 1] == '|')
	{
		bff[j] = 0;
		j++;
		inff->cmd_buf_type = CMD_OR;
	}
	else if (bff[j] == '&' && bff[j + 1] == '&')
	{
		bff[j] = 0;
		j++;
		inff->cmd_buf_type = CMD_AND;
	}
	else if (bff[j] == ';')
	{
		bff[j] = 0;
		inff->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*g = j;
	return (1);
}

/**
 * check_chain - determines whether to continue
 * chaining based on the last status.
 * @inff: structure parameter
 * @bff: char buff
 * @g: ddress of the current position in buf.
 * @i: start of buf position
 * @len: buffer length
 *
 * Return: null
 */
void check_chain(info_t *inff, char *bff, size_t *g, size_t i, size_t len)
{
	size_t j = *g;

	if (inff->cmd_buf_type == CMD_AND)
	{
		if (inff->status)
		{
			bff[i] = 0;
			j = len;
		}
	}
	if (inff->cmd_buf_type == CMD_OR)
	{
		if (!inff->status)
		{
			bff[i] = 0;
			j = len;
		}
	}

	*g = j;
}

/**
 * replace_alias - performs alias replacement
 *  in the tokenized string.
 * @inff: structure parameter.
 * Return: if it is replaced return 1,
 *  if other 0
 */
int replace_alias(info_t *inff)
{
	int i;
	list_t *node;
	char *g;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(inff->alias, inff->argv[0], '=');
		if (!node)
			return (0);
		free(inff->argv[0]);
		g = _strchr(node->str, '=');
		if (!g)
			return (0);
		g = _strdup(g + 1);
		if (!g)
			return (0);
		inff->argv[0] = g;
	}
	return (1);
}

/**
 * replace_vars - performs variable replacement
 *  in the tokenized string.
 * @inff: structure paramter
 * Return: if it is replaced return 1,
 *   if other 0
 */
int replace_vars(info_t *inff)
{
	int i = 0;
	list_t *node;

	for (i = 0; inff->argv[i]; i++)
	{
		if (inff->argv[i][0] != '$' || !inff->argv[i][1])
			continue;

		if (!_strcmp(inff->argv[i], "$?"))
		{
			replace_string(&(inff->argv[i]),
				_strdup(convert_number(inff->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inff->argv[i], "$$"))
		{
			replace_string(&(inff->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inff->env, &inff->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inff->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inff->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces occurrences of a string.
 * @old: old string's address
 * @new: the new strng
 *
 * Return: if it is replaced return 1,
 * if other 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

