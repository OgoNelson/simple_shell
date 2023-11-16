#include "shell.h"

/**
 * _myEnv - prints the current environment
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myEnv(info_t *data)
{
	printlist_str(data->_env);
	return (0);
}

/**
 * _getEnv - gets the value of an environ variable
 * @input: Structure containing potential arguments. Used to maintain
 * @namev: env var name
 *
 * Return: the value
 */
char *_getEnv(info_t *input, const char *namev)
{
	list_t *_node = input->_env;
	char *o;

	while (_node)
	{
		o = startstr(_node->_str, namev);
		if (o && *o)
			return (o);
		_node = _node->_next;
	}
	return (NULL);
}

/**
 * _mysetEnv - Initialize a new environment variable,
 *             or modify an existing one
 * @input: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetEnv(info_t *input)
{
	if (input->argc != 3)
	{
		_putsE("Incorrect number of arguements\n");
		return (1);
	}
	if (_setEnv(input, input->argv[1], input->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetEnv - Remove an environment variable
 * @input: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetEnv(info_t *input)
{
	int j;

	if (input->argc == 1)
	{
		_putsE("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= input->argc; j++)
		_unsetEnv(input, input->argv[j]);

	return (0);
}

/**
 * populateEnv_list - populates env linked list
 * @input: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populateEnv_list(info_t *input)
{
	list_t *_node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		addnode_end(&_node, environ[j], 0);
	input->_env = _node;
	return (0);
}
