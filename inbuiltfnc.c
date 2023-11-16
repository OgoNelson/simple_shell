#include "shell.h"

/**
 * _exitShell - exits the shell
 * @input: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if input.argv[0] != "exit"
 */
int _exitshell(info_t *input)
{
	int exitchecker;

	if (input->argv[1])  /* If there is an exit arguement */
	{
		exitchecker = _strtoint(input->argv[1]);
		if (exitchecker == -1)
		{
			input->_status = 2;
			print_E(input, "Illegal number: ");
			_putsE(input->argv[1]);
			_putcharE('\n');
			return (1);
		}
		input->error_num = _strtoint(input->argv[1]);
		return (-2);
	}
	input->error_num = -1;
	return (-2);
}

/**
 * _cdir - changes the current directory of the process
 * @input: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _cdir(info_t *input)
{
	char *c, *dir, buffer[1024];
	int cdir_ret;

	c = getcwd(buffer, 1024);
	if (!c)
		_putstr("TODO: >>getcwd failure emsg here<<\n");
	if (!input->argv[1])
	{
		dir = _getEnv(input, "HOME=");
		if (!dir)
			cdir_ret =
				chdir((dir = _getEnv(input, "PWD=")) ? dir : "/");
		else
			cdir_ret = chdir(dir);
	}
	else if (_mystrcomp(input->argv[1], "-") == 0)
	{
		if (!_getEnv(input, "OLDPWD="))
		{
			_putstr(c);
			_myputchar('\n');
			return (1);
		}
		_putstr(_getEnv(input, "OLDPWD=")), _myputchar('\n');
		cdir_ret = /* TODO: what should this be? */
			chdir((dir = _getEnv(input, "OLDPWD=")) ? dir : "/");
	}
	else
		cdir_ret = chdir(input->argv[1]);
	if (cdir_ret == -1)
	{
		print_E(input, "can't cd to ");
		_putsE(input->argv[1]), _putcharE('\n');
	}
	else
	{
		_setEnv(input, "OLDPWD", _getEnv(input, "PWD="));
		_setEnv(input, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _helper - changes the current directory of the process
 * @input: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _helper(info_t *input)
{
	char **arg_ar;

	arg_ar = input->argv;
	_putstr("help call works. Function not yet implemented \n");
	if (0)
		_putstr(*arg_ar); /* shows temp att_unused workaround */
	return (0);
}
