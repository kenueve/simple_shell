#include "shell.h"

/**
 * _myhistory - shows a history list.
 * @info: struct holds potential args and
 * preserve a constant function prototype.
 *  Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - alias --> string
 * @info: structure parameter
 * @str: alais strg.
 *
 * Return: 0 when its working.
 *         1 if error occurs.
 */
int unset_alias(info_t *info, char *str)
{
	char *b, a;
	int ret;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	a = *b;
	*b = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = a;
	return (ret);
}

/**
 * set_alias - alias --> string
 * @info: structure parameter.
 * @str: string alias.
 *
 * Return: 0 when its working.
 *         1 if error occurs.
 */
int set_alias(info_t *info, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - string alias printing.
 * @nde: nde's alias.
 *
 * Return: 0 if its working.
 * 1 if wrror occurs.
 */
int print_alias(list_t *nde)
{
	char *b = NULL, *a = NULL;

	if (nde)
	{
		b = _strchr(nde->str, '=');
		for (a = nde->str; a <= b; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Emulates the behavior of
 *  the alias builtin command (refer to 'man alias').
 * @info: struct holding potential args
 * to maintain a consistent function prototyp.
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int u = 0;
	char *b = NULL;
	list_t *nde = NULL;

	if (info->argc == 1)
	{
		nde = info->alias;
		while (nde)
		{
			print_alias(nde);
			nde = nde->next;
		}
		return (0);
	}
	for (u = 1; info->argv[u]; u++)
	{
		b = _strchr(info->argv[u], '=');
		if (b)
			set_alias(info, info->argv[u]);
		else
			print_alias(node_starts_with(info->alias, info->argv[u], '='));
	}

	return (0);
}

