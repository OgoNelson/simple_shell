#include "shell.h"

/**
 * addnode - adds a node to the start of the list
 * @hptr: address of pointer to head node
 * @_str: str field of node
 * @numb: node index used by history
 *
 * Return: size of list
 */
list_t *addnode(list_t **hptr, const char *_str, int numb)
{
	list_t *newhead;

	if (!hptr)
		return (NULL);
	newhead = malloc(sizeof(list_t));
	if (!newhead)
		return (NULL);
	_mymemset((void *)newhead, 0, sizeof(list_t));
	newhead->_num = numb;
	if (_str)
	{
		newhead->_str = _mystrdupli(_str);
		if (!newhead->_str)
		{
			free(newhead);
			return (NULL);
		}
	}
	newhead->_next = *hptr;
	*hptr = newhead;
	return (newhead);
}

/**
 * addnode_end - adds a node to the end of the list
 * @hptr: address of pointer to head node
 * @_str: str field of node
 * @numb: node index used by history
 *
 * Return: size of list
 */
list_t *addnode_end(list_t **hptr, const char *_str, int numb)
{
	list_t *newnode, *_node;

	if (!hptr)
		return (NULL);

	_node = *hptr;
	newnode = malloc(sizeof(list_t));
	if (!newnode)
		return (NULL);
	_mymemset((void *)newnode, 0, sizeof(list_t));
	new_node->_num = numb;
	if (_str)
	{
		newnode->_str = _mystrdupli(_str);
		if (!newnode->_str)
		{
			free(newnode);
			return (NULL);
		}
	}
	if (_node)
	{
		while (_node->_next)
			_node = _node->_next;
		_node->_next = newnode;
	}
	else
		*hptr = newnode;
	return (newnode);
}

/**
 * printlist_str - prints only the str element of a list_t linked list
 * @ptr: pointer to first node
 *
 * Return: size of list
 */
size_t printlist_str(const list_t *ptr)
{
	size_t j = 0;

	while (ptr)
	{
		_putstr(ptr->_str ? ptr->_str : "(nil)");
		_putstr("\n");
		ptr = ptr->_next;
		j++;
	}
	return (j);
}

/**
 * delete_node_index - deletes node at given index
 * @hptr: address of pointer to first node
 * @_index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_index(list_t **hptr, unsigned int _index)
{
	list_t *_node, *prevnode;
	unsigned int j = 0;

	if (!hptr || !*hptr)
		return (0);

	if (!_index)
	{
		_node = *hptr;
		*hptr = (*hptr)->_next;
		free(_node->_str);
		free(_node);
		return (1);
	}
	_node = *hptr;
	while (_node)
	{
		if (j == _index)
		{
			prevnode->_next = _node->_next;
			free(_node->_str);
			free(_node);
			return (1);
		}
		j++;
		prevnode = _node;
		_node = _node->_next;
	}
	return (0);
}

/**
 * freelist - frees all nodes of a list
 * @headptr: address of pointer to head node
 *
 * Return: void
 */
void freelist(list_t **headptr)
{
	list_t *_node, *nextnode, *_head;

	if (!headptr || !*headptr)
		return;
	_head = *headptr;
	_node = _head;
	while (_node)
	{
		nextnode = _node->_next;
		free(_node->_str);
		free(_node);
		_node = nextnode;
	}
	*headptr = NULL;
}
