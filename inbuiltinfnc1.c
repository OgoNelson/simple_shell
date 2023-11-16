#include "shell.h"

/**
 * _myhist - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhist(info_t *data)
{
	printlist(data->myhistory);
	return (0);
}

/**
 * unsetalias - sets alias to string
 * @input: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetalias(info_t *input, char *s)
{
	char *o, h;
	int _ret;

	o = _mystrchr(s, '=');
	if (!o)
		return (1);
	h = *o;
	*o = 0;
	_ret = delete_node_index(&(input->myalias),
		getnode_index(input->myalias, node_starts(input->myalias, s, -1)));
	*o = h;
	return (_ret);
}

/**
 * setalias - sets alias to string
 * @input: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setalias(info_t *input, char *s)
{
	char *o;

	o = _mystrchr(s, '=');
	if (!o)
		return (1);
	if (!*++o)
		return (unsetalias(input, s));

	unsetalias(input, s);
	return (addnode_end(&(input->myalias), s, 0) == NULL);
}

/**
 * printalias - prints an alias string
 * @mynode: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printalias(list_t *mynode)
{
	char *o = NULL, *b = NULL;

	if (mynode)
	{
		o = _mystrchr(mynode->_str, '=');
		for (b = mynode->_str; b <= o; b++)
			_myputchar(*b);
		_myputchar('\'');
		_putstr(o + 1);
		_putstr("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myshellalias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myshellalias(info_t *data)
{
	int j = 0;
	char *o = NULL;
	list_t *_node = NULL;

	if (data->argc == 1)
	{
		_node = data->myalias;
		while (_node)
		{
			printalias(_node);
			_node = _node->_next;
		}
		return (0);
	}
	for (j = 1; data->argv[j]; j++)
	{
		o = _mystrchr(data->argv[j], '=');
		if (o)
			setalias(data, data->argv[j]);
		else
			printalias(node_starts(data->myalias, data->argv[j], '='));
	}

	return (0);
}
