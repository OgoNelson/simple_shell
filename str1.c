#include "shell.h"

/**
 * _mystrcpy - copies a string
 * @cpydest: the destination
 * @cpysrc: the source
 *
 * Return: pointer to destination
 */
char *_mystrcpy(char *cpydest, char *cpysrc)
{
	int j = 0;

	if (cpydest == cpysrc || cpysrc == 0)
		return (cpydest);
	while (cpysrc[j])
	{
		cpydest[j] = cpysrc[j];
		j++;
	}
	cpydest[j] = 0;
	return (cpydest);
}

/**
 * _mystrdupli - duplicates a string
 * @strdupli: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_mystrdupli(const char *strdupli)
{
	int _length = 0;
	char *_ret;

	if (strdupli == NULL)
		return (NULL);
	while (*strdupli++)
		_length++;
	_ret = malloc(sizeof(char) * (_length + 1));
	if (!_ret)
		return (NULL);
	for (_length++; _length--;)
		_ret[_length] = *--_str;
	return (_ret);
}

/**
 *_putstr - prints an input string
 *@pstr: the string to be printed
 *
 * Return: Nothing
 */
void _putstr(char *pstr)
{
	int j = 0;

	if (!pstr)
		return;
	while (pstr[j] != '\0')
	{
		_myputchar(pstr[j]);
		j++;
	}
}

/**
 * _myputchar - writes the character h to stdout
 * @h: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _myputchar(char h)
{
	static int j;
	static char buffer[WRITE_BUF_SIZE];

	if (h == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buffer, j);
		j = 0;
	}
	if (h != BUF_FLUSH)
		buffer[j++] = h;
	return (1);
}
