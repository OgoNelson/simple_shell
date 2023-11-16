#include "shell.h"

/**
 * deli_chain - test if current char in buffer is a chain delimeter
 * @input: the parameter struct
 * @buffer: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int deli_chain(info_t *input, char *buffer, size_t *ptr)
{
	size_t i = *ptr;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		input->cmdbuf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		input->cmdbuf_type = CMD_AND;
	}
	else if (buffer[i] == ';') /* found end of this command */
	{
		buffer[i] = 0; /* replace semicolon with null */
		input->cmdbuf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}

/**
 * checkchain - checks we should continue chaining based on last status
 * @input: the parameter struct
 * @buffer: the char buffer
 * @ptr: address of current position in buf
 * @i: starting position in buf
 * @_len: length of buf
 *
 * Return: Void
 */
void checkchain(info_t *input, char *buffer, size_t *ptr, size_t i, size_t _len)
{
	size_t j = *ptr;

	if (input->cmdbuf_type == CMD_AND)
	{
		if (input->_status)
		{
			buffer[i] = 0;
			j = _len;
		}
	}
	if (input->cmdbuf_type == CMD_OR)
	{
		if (!input->_status)
		{
			buffer[i] = 0;
			j = _len;
		}
	}

	*ptr = j;
}

/**
 * replace_myalias - replaces an aliases in the tokenized string
 * @input: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_myalias(info_t *input)
{
	int j;
	list_t *_node;
	char *o;

	for (j = 0; j < 10; j++)
	{
		_node = node_starts(input->myalias, input->argv[0], '=');
		if (!_node)
			return (0);
		free(input->argv[0]);
		o = _mystrchr(_node->_str, '=');
		if (!o)
			return (0);
		o = _mystrdupli(o + 1);
		if (!o)
			return (0);
		input->argv[0] = o;
	}
	return (1);
}

/**
 * replace_myvars - replaces vars in the tokenized string
 * @input: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_myvars(info_t *input)
{
	int j = 0;
	list_t *_node;

	for (j = 0; input->argv[j]; j++)
	{
		if (input->argv[j][0] != '$' || !input->argv[j][1])
			continue;

		if (!_mystrcomp(input->argv[j], "$?"))
		{
			replace_mystring(&(input->argv[j]),
				_mystrdupli(convertnumb(input->_status, 10, 0)));
			continue;
		}
		if (!_mystrcomp(input->argv[j], "$$"))
		{
			replace_string(&(input->argv[j]),
				_mystrdupli(convertnumb(getpid(), 10, 0)));
			continue;
		}
		_node = node_starts(input->_env, &input->argv[j][1], '=');
		if (_node)
		{
			replace_mystring(&(input->argv[j]),
				_mystrdupli(_mystrchr(_node->_str, '=') + 1));
			continue;
		}
		replace_mystring(&input->argv[j], _mystrdupli(""));

	}
	return (0);
}

/**
 * replace_mystring - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_mystring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
