#include "shell.h"

/**
 * gethistory_file - gets the history file
 * @input: parameter struct
 *
 * Return: allocated string containg history file
 */

char *gethistory_file(info_t *input)
{
	char *_buf, *_dir;

	_dir = _getEnv(input, "HOME=");
	if (!_dir)
		return (NULL);
	_buf = malloc(sizeof(char) * (_mystrlen(_dir) + _mystrlen(HIST_FILE) + 2));
	if (!_buf)
		return (NULL);
	_buf[0] = 0;
	_mystrcpy(_buf, _dir);
	_strconcat(_buf, "/");
	_strconcat(_buf, HIST_FILE);
	return (_buf);
}

/**
 * write_hist - creates a file, or appends to an existing file
 * @input: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(info_t *input)
{
	ssize_t fdes;
	char *_filename = gethistory_file(input);
	list_t *_node = NULL;

	if (!_filename)
		return (-1);

	fdes = open(_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(_filename);
	if (fdes == -1)
		return (-1);
	for (_node = input->myhistory; _node; _node = _node->_next)
	{
		_putstrfd(_node->_str, fdes);
		_wputfd('\n', fdes);
	}
	_wputfd(BUF_FLUSH, fdes);
	close(fdes);
	return (1);
}

/**
 * read_hist - reads history from file
 * @input: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist(info_t *input)
{
	int j, _last = 0, _linecount = 0;
	ssize_t fdes, _rdlen, filesize = 0;
	struct stat _st;
	char *_buf = NULL, *_filename = gethistory_file(input);

	if (!_filename)
		return (0);

	fdes = open(_filename, O_RDONLY);
	free(_filename);
	if (fdes == -1)
		return (0);
	if (!fstat(fdes, &_st))
		filesize = _st.st_size;
	if (filesize < 2)
		return (0);
	_buf = malloc(sizeof(char) * (filesize + 1));
	if (!_buf)
		return (0);
	_rdlen = read(fdes, _buf, filesize);
	_buf[filesize] = 0;
	if (_rdlen <= 0)
		return (free(_buf), 0);
	close(fdes);
	for (j = 0; j < filesize; j++)
		if (_buf[j] == '\n')
		{
			_buf[j] = 0;
			buildhistory_list(input, _buf + _last, _linecount++);
			_last = j + 1;
		}
	if (_last != j)
		buildhistory_list(input, _buf + _last, _linecount++);
	free(_buf);
	input->_histcount = _linecount;
	while (input->_histcount-- >= HIST_MAX)
		delete_node_index(&(input->myhistory), 0);
	renumber_hist(input);
	return (input->_histcount);
}

/**
 * buildhistory_list - adds entry to a history linked list
 * @input: Structure containing potential arguments. Used to maintain
 * @_buf: buffer
 * @_linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildhistory_list(info_t *input, char *_buf, int _linecount)
{
	list_t *_node = NULL;

	if (input->myhistory)
		_node = input->myhistory;
	addnode_end(&_node, _buf, _linecount);

	if (!input->myhistory)
		input->myhistory = _node;
	return (0);
}

/**
 * renumber_hist - renumbers the history linked list after changes
 * @input: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_hist(info_t *input)
{
	list_t *_node = input->myhistory;
	int j = 0;

	while (_node)
	{
		_node->_num = j++;
		_node = _node->_next;
	}
	return (input->_histcount = j);
}
