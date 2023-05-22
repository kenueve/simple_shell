#include "shell.h"

/**
 * hsh - main loop for the program.
 * @inff:  inff structure return and parameter.
 * @argv: the arg vector from main.
 *
 * Return: if it succeed return 0
 *  if other 1
 */
int hsh(info_t *inff, char **argv)
{
	ssize_t e = 0;
	int b_ret = 0;

	while (e != -1 && b_ret != -2)
	{
		clear_info(inff);
		if (interactive(inff))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		e = get_input(inff);
		if (e != -1)
		{
			set_info(inff, argv);
			b_ret = find_builtin(inff);
			if (b_ret == -1)
				find_cmd(inff);
		}
		else if (interactive(inff))
			_putchar('\n');
		free_info(inff, 0);
	}
	write_history(inff);
	free_info(inff, 1);
	if (!interactive(inff) && inff->status)
		exit(inff->status);
	if (b_ret == -2)
	{
		if (inff->err_num == -1)
			exit(inff->status);
		exit(inff->err_num);
	}
	return (b_ret);
}

/**
 * find_builtin - searches for a builtin cmd.
 * @inff: inff structure return and parameter.
 *
 * Return:  if the builtin command is not found
 *    return -1
 *			if the builtinis successful
 *    return 0
 *			if builtin found but doesn't succeed
 *    return 1
 *		    if builtin signals exit,
 *    return -2
 */
int find_builtin(info_t *inff)
{
	int l, b_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (l = 0; builtintbl[l].type; l++)
		if (_strcmp(inff->argv[0], builtintbl[l].type) == 0)
		{
			inff->line_count++;
			b_in_ret = builtintbl[l].func(inff);
			break;
		}
	return (b_in_ret);
}

/**
 * find_cmd - ocates a cmd in the PATH.
 * @inff: parameter and return inff struct.
 *
 * Return: null
 */
void find_cmd(info_t *inff)
{
	char *path = NULL;
	int l, h;

	inff->path = inff->argv[0];
	if (inff->linecount_flag == 1)
	{
		inff->line_count++;
		inff->linecount_flag = 0;
	}
	for (l = 0, h = 0; inff->arg[l]; l++)
		if (!is_delim(inff->arg[l], " \t\n"))
			h++;
	if (!h)
		return;

	path = find_path(inff, _getenv(inff, "PATH="), inff->argv[0]);
	if (path)
	{
		inff->path = path;
		fork_cmd(inff);
	}
	else
	{
		if ((interactive(inff) || _getenv(inff, "PATH=")
			|| inff->argv[0][0] == '/') && is_cmd(inff, inff->argv[0]))
			fork_cmd(inff);
		else if (*(inff->arg) != '\n')
		{
			inff->status = 127;
			print_error(inff, "not found\n");
		}
	}
}

/**
 * fork_cmd - creates a new process to
 *  execute the specified cmd.
 * @inff: parameter and return structure inff.
 * Return: null
 */
void fork_cmd(info_t *inff)
{
	pid_t c_pid;

	c_pid = fork();
	if (c_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (c_pid == 0)
	{
		if (execve(inff->path, inff->argv, get_environ(inff)) == -1)
		{
			free_info(inff, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inff->status));
		if (WIFEXITED(inff->status))
		{
			inff->status = WEXITSTATUS(inff->status);
			if (inff->status == 126)
				print_error(inff, "Permission denied\n");
		}
	}
}
