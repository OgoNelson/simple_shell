#include "shell.h"

/**
 *_putsE - prints an input string
 * @_str: the string to be printed
 *
 * Return: Nothing
 */
void _putsE(char *_str)
{
	int j = 0;

	if (!_str)
		return;
	while (_str[j] != '\0')
	{
		_putcharE(_str[j]);
		j++;
	}
}

/**
 * _putcharE - inputs the character h to stderr
 * @h: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putcharE(char h)
{
	static int j;
	static char buffer[WRITE_BUF_SIZE];

	if (h == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buffer, j);
		j = 0;
	}
	if (h != BUF_FLUSH)
		buffer[j++] = h;
	return (1);
}

/**
 * _wputfd - writes the character c to given fd
 * @h: The character to print
 * @filedes: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _wputfd(char h, int filedes)
{
	static int j;
	static char buffer[WRITE_BUF_SIZE];

	if (h == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(filedes, buffer, j);
		j = 0;
	}
	if (h != BUF_FLUSH)
		buffer[j++] = h;
	return (1);
}

/**
 *_putstrfd - prints an input string
 * @_str: the string to be printed
 * @filedes: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putstrfd(char *_str, int filedes)
{
	int j = 0;

	if (!_str)
		return (0);
	while (*_str)
	{
		j += _wputfd(*_str++, filedes);
	}
	return (j);
}
