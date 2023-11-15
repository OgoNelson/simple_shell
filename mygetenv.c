#include "shell.h"

/**
 * getEnviron - returns the string array copy of our environ
 * @input: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **getEnviron(info_t *input)
{
	if (!input->myenviron || input->envchanged)
	{
		input->myenviron = list_to_str(input->_env);
		input->envchanged = 0;
	}

	return (input->myenviron);
}

/**
 * _unsetEnv - Remove an environment variable
 * @input: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @strvar: the string env var property
 */
int _unsetEnv(info_t *input, char *strvar)
{
	list_t *_node = input->_env;
	size_t j = 0;
	char *o;

	if (!_node || !strvar)
		return (0);

	while (_node)
	{
		o = startstr(_node->_str, strvar);
		if (o && *o == '=')
		{
			input->envchanged = delete_node_index(&(input->_env), j);
			j = 0;
			_node = input->_env;
			continue;
		}
		_node = _node->_next;
		j++;
	}
	return (input->envchanged);
}

/**
 * _setEnv - Initialize a new environment variable,
 *             or modify an existing one
 * @input: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @strvar: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setEnv(info_t *input, char *strvar, char *val)
{
	char *buffer = NULL;
	list_t *_node;
	char *o;

	if (!strvar || !val)
		return (0);

	buffer = malloc(_mystrlen(strvar) + _mystrlen(val) + 2);
	if (!buffer)
		return (1);
	_mystrcpy(buffer, strvar);
	_strconcat(buffer, "=");
	_strconcat(buffer, val);
	node = input->_env;
	while (_node)
	{
		o = startstr(_node->_str, strvar);
		if (o && *o == '=')
		{
			free(_node->_str);
			_node->_str = buffer;
			input->envchanged = 1;
			return (0);
		}
		_node = _node->_next;
	}
	addnode_end(&(input->_env), buffer, 0);
	free(buffer);
	input->envchanged = 1;
	return (0);
}
