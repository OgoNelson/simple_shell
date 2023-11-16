#include "shell.h"

/**
 * listlen - determines length of linked list
 * @ptr: pointer to first node
 *
 * Return: size of list
 */
size_t listlen(const list_t *ptr)
{
	size_t j = 0;

	while (ptr)
	{
		ptr = ptr->_next;
		j++;
	}
	return (j);
}

/**
 * list_to_str - returns an array of strings of the list->_str
 * @ptr: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_str(list_t *ptr)
{
	list_t *_node = ptr;
	size_t i = listlen(ptr), j;
	char **_strs;
	char *_str;

	if (!ptr || !i)
		return (NULL);
	_strs = malloc(sizeof(char *) * (i + 1));
	if (!_strs)
		return (NULL);
	for (i = 0; _node; _node = _node->_next, i++)
	{
		_str = malloc(_mystrlen(_node->_str) + 1);
		if (!_str)
		{
			for (j = 0; j < i; j++)
				free(_strs[j]);
			free(_strs);
			return (NULL);
		}

		_str = _mystrcpy(_str, _node->_str);
		_strs[i] = _str;
	}
	_strs[i] = NULL;
	return (_strs);
}


/**
 * printlist - prints all elements of a list_t linked list
 * @ptr: pointer to first node
 *
 * Return: size of list
 */
size_t printlist(const list_t *ptr)
{
	size_t j = 0;

	while (ptr)
	{
		_putstr(convertnumb(ptr->_num, 10, 0));
		_myputchar(':');
		_myputchar(' ');
		_putstr(ptr->_str ? ptr->_str : "(nil)");
		_putstr("\n");
		ptr = ptr->_next;
		j++;
	}
	return (j);
}

/**
 * node_starts - returns node whose string starts with prefix
 * @_node: pointer to list head
 * @str: string to match
 * @h: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts(list_t *_node, char *str, char h)
{
	char *o = NULL;

	while (_node)
	{
		o = startstr(_node->_str, str);
		if (o && ((h == -1) || (*o == h)))
			return (_node);
		_node = _node->_next;
	}
	return (NULL);
}

/**
 * getnode_index - gets the index of a node
 * @hptr: pointer to list head
 * @_node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getnode_index(list_t *hptr, list_t *_node)
{
	size_t j = 0;

	while (hptr)
	{
		if (hptr == _node)
			return (j);
		hptr = hptr->_next;
		j++;
	}
	return (-1);
}
