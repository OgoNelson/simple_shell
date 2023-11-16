#include "shell.h"

/**
 * clearinfo - initializes info_t struct
 * @input: struct address
 */
void clearinfo(info_t *input)
{
	input->arg = NULL;
	input->argv = NULL;
	input->_path = NULL;
	input->argc = 0;
}

/**
 * setinfo - initializes info_t struct
 * @input: struct address
 * @av: argument vector
 */
void setinfo(info_t *input, char **av)
{
	int j = 0;

	input->filename = av[0];
	if (input->arg)
	{
		input->argv = strtowrd(input->arg, " \t");
		if (!input->argv)
		{

			input->argv = malloc(sizeof(char *) * 2);
			if (input->argv)
			{
				input->argv[0] = _mystrdupli(input->arg);
				input->argv[1] = NULL;
			}
		}
		for (j = 0; input->argv && input->argv[j]; j++)
			;
		input->argc = j;

		replace_myalias(input);
		replace_myvars(input);
	}
}

/**
 * freeinfo - frees info_t struct fields
 * @input: struct address
 * @allf: true if freeing all fields
 * Return: void
 */
void freeinfo(info_t *input, int allf)
{
	freestr(input->argv);
	input->argv = NULL;
	input->_path = NULL;
	if (allf)
	{
		if (!input->cmdbuf)
			free(input->arg);
		if (input->_env)
			freelist(&(input->_env));
		if (input->myhistory)
			freelist(&(input->myhistory));
		if (input->myalias)
			freelist(&(input->myalias));
		freestr(input->myenviron);
			input->myenviron = NULL;
		freeptr((void **)input->cmdbuf);
		if (input->inputdir > 2)
			close(input->inputdir);
		_myputchar(BUF_FLUSH);
	}
}
