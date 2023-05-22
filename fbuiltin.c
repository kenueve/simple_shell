#include "shell.h"

/**
 * _myexit - exit shell
 * @info:  struct holds potential args and
 * preserve a constant function prototype.
 *  Return: terminates the program with
 *  a specified exit status.
 *  returns 0 if info.argv[0]
 *  is not equal to "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change the current directory.
 * @info: struct holds potential args and
 * preserve a constant function prototype.
 *  Return: 0
 */
int _mycd(info_t *info)
{
	char *c, *dr, bf[1024];
	int chdir_ret;

	c = getcwd(bf, 1024);
	if (!c)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dr = _getenv(info, "HOME=");
		if (!dr)
			chdir_ret = /* TODO: what should this be? */
				chdir((dr = _getenv(info, "PWD=")) ? dr : "/");
		else
			chdir_ret = chdir(dr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dr = _getenv(info, "OLDPWD=")) ? dr : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(bf, 1024));
	}
	return (0);
}

/**
 * _myhelp - change current directory.
 * @info: struct holds potential args and
 * preserve a constant function prototype.
 *  Return: 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

