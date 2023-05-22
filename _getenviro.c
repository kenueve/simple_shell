#include "shell.h"

/**
 * get_environ - returns a cpy of
 * string array representing our environ.
 * @inff: structure holding potential args
 *  to maintain a consistent function prototyp.
 * Return: 0
 */
char **get_environ(info_t *inff)
{
	if (!inff->environ || inff->env_changed)
	{
		inff->environ = list_to_strings(inff->env);
		inff->env_changed = 0;
	}

	return (inff->environ);
}

/**
 * _unsetenv -deletes env variable.
 * @inff: structure holding potential args
 *  to maintain a consistent function prototype.
 * @var: string env variable property
 * *  Return: on delete = 1
 *  other = 0
 */
int _unsetenv(info_t *inff, char *var)
{
	list_t *node = inff->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			inff->env_changed = delete_node_at_index(&(inff->env), i);
			i = 0;
			node = inff->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inff->env_changed);
}

/**
 * _setenv - generates new env variable,
 *   or modifes existing one.
 * @inff: structure holding potential args
 *  to maintain a consistent function prototyp.
 * @var: string env variable property.
 * @value: string env variable value.
 *  Return: 0
 */
int _setenv(info_t *inff, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = inff->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			inff->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inff->env), buf, 0);
	free(buf);
	inff->env_changed = 1;
	return (0);
}

