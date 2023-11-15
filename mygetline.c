#include "shell.h"

/**
 * inputbuf - buffers chained commands
 * @input: parameter struct
 * @_buf: address of buffer
 * @_len: address of len var
 *
 * Return: bytes read
 */
ssize_t inputbuf(info_t *input, char **_buf, size_t *_len)
{
	ssize_t s = 0;
	size_t lenp = 0;

	if (!*_len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*_buf);
		*_buf = NULL;
		signal(SIGINT, sigint_Handler);
#if USE_GETLINE
		s = getline(_buf, &lenp, stdin);
#else
		s = _getline(input, _buf, &lenp);
#endif
		if (s > 0)
		{
			if ((*_buf)[s - 1] == '\n')
			{
				(*_buf)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			input->linecountflag = 1;
			remove_comments(*_buf);
			buildhistory_list(input, *_buf, input->_histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*_len = s;
				input->cmdbuf = _buf;
			}
		}
	}
	return (s);
}

/**
 * getinput - gets a line minus the newline
 * @input: parameter struct
 *
 * Return: bytes read
 */
ssize_t getinput(info_t *input)
{
	static char *_buf; /* the ';' command chain buffer */
	static size_t i, j, _len;
	ssize_t s = 0;
	char **bufp = &(input->arg), *ptr;

	_myputchar(BUF_FLUSH);
	s = inputbuf(input, &_buf, &_len);
	if (s == -1) /* EOF */
		return (-1);
	if (_len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		ptr = _buf + i; /* get pointer for return */

		checkchain(input, _buf, &j, i, _len);
		while (j < _len) /* iterate to semicolon or end */
		{
			if (deli_chain(input, _buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= _len) /* reached end of buffer? */
		{
			i = _len = 0; /* reset position and length */
			input->cmdbuf_type = CMD_NORM;
		}

		*bufp = ptr; /* pass back pointer to current command position */
		return (_mystrlen(ptr)); /* return length of current command */
	}

	*bufp = _buf; /* else not a chain, pass back buffer from _getline() */
	return (s); /* return length of buffer from _getline() */
}

/**
 * readbuf - reads a buffer
 * @input: parameter struct
 * @_buf: buffer
 * @i: size
 *
 * Return: s
 */
ssize_t readbuf(info_t *input, char *_buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	r = read(input->inputdir, _buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * _mygetline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _mygetline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = readbuf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _mystrchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _reallocmem(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strnconcat(new_p, buf + i, k - i);
	else
		_mystrncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_Handler - blocks ctrl-C
 * @signum: the signal number
 *
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int signum)
{
	_putstr("\n");
	_putstr("$ ");
	_myputchar(BUF_FLUSH);
}
