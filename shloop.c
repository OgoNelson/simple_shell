#include "shell.h"

/**
 * shloop - main shell loop
 * @data: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shloop(info_t *data, char **av)
{
	ssize_t s = 0;
	int builtin = 0;

	while (s != -1 && builtin != -2)
	{
		clearinfo(data);
		if (interactive(data))
			_putstr("$ ");
		_putcharE(BUF_FLUSH);
		s = getinput(data);
		if (s != -1)
		{
			setinfo(data, av);
			builtin = findbuiltin(data);
			if (builtin == -1)
				findcmd(data);
		}
		else if (interactive(data))
			_myputchar('\n');
		freeinfo(data, 0);
	}
	write_hist(data);
	freeinfo(data, 1);
	if (!interactive(data) && data->_status)
		exit(data->_status);
	if (builtin == -2)
	{
		if (data->error_num == -1)
			exit(data->_status);
		exit(data->error_num);
	}
	return (builtin);
}

/**
 * findbuiltin - finds a builtin command
 * @data: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int findbuiltin(info_t *data)
{
	int j, builtin_ret = -1;
	builtin_table builtintable[] = {
		{"exit", _exitshell},
		{"env", _myEnv},
		{"help", _helper},
		{"history", _myhist},
		{"setenv", _mysetEnv},
		{"unsetenv", _myunsetEnv},
		{"cd", _cdir},
		{"alias", _myshellalias},
		{NULL, NULL}
	};

	for (j = 0; builtintable[j].type; j++)
		if (_strcmp(data->argv[0], builtintable[j].type) == 0)
		{
			data->linecount++;
			builtin_ret = builtintable[j].func(data);
			break;
		}
	return (builtin_ret);
}

/**
 * findcmd - finds a command in PATH
 * @input: the parameter & return info struct
 *
 * Return: void
 */
void findcmd(info_t *input)
{
	char *_path = NULL;
	int j, l;

	input->_path = input->argv[0];
	if (input->linecountflag == 1)
	{
		input->linecount++;
		input->linecountflag = 0;
	}
	for (j = 0, l = 0; input->arg[j]; j++)
		if (!my_delim(input->arg[j], " \t\n"))
			l++;
	if (!l)
		return;

	_path = find_cmd(input, _getEnv(input, "PATH="), input->argv[0]);
	if (_path)
	{
		input->_path = _path;
		forkcmd(input);
	}
	else
	{
		if ((interactive(input) || _getEnv(input, "PATH=")
			|| input->argv[0][0] == '/') && exec_cmd(input, input->argv[0]))
			forkcmd(input);
		else if (*(input->arg) != '\n')
		{
			input->_status = 127;
			print_E(info, "not found\n");
		}
	}
}

/**
 * forkcmd - forks a an exec thread to run cmd
 * @input: the parameter & return info struct
 *
 * Return: void
 */
void forkcmd(info_t *input)
{
	pid_t childpid;

	childpid = fork();
	if (childpid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (childpid == 0)
	{
		if (execve(input->_path, input->argv, getEnviron(input)) == -1)
		{
			freeinfo(input, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(input->_status));
		if (WIFEXITED(input->_status))
		{
			input->_status = WEXITSTATUS(input->_status);
			if (input->_status == 126)
				print_E(input, "Permission denied\n");
		}
	}
}
