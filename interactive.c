#include "shell.h"

/**
 * interact - returns true if shell is in interactive mode
 * @data: struct address
 *
 * Return: 1 if in interactive mode, 0 if not
 */
int interact(info_t *data)
{
	return (isatty(STDIN_FILENO) && data->inputdir <= 2);
}

/**
 * my_delim - verify if char is a delimeter
 * @h: char to check
 * @mydelim: the delimeter
 * Return: 1 if true, 0 if false
 */
int my_delim(char h, char *mydelim)
{
	while (*mydelim)
		if (*mydelim++ == h)
			return (1);
	return (0);
}

/**
 *_alpha - checks for alphabet
 *@h: input char
 *Return: 1 if h is alphabetic, 0 if not
 */

int _alpha(int h)
{
	if ((h >= 'a' && h <= 'z') || (h >= 'A' && h <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *interactive - converts a string to an int
 *@c: the string to be converted
 *Return: converted number otherwise 0
 */

int interactive(char *c)
{
	int j, _sign = 1, _flag = 0, _output;
	unsigned int convresult = 0;

	for (j = 0;  c[j] != '\0' && _flag != 2; j++)
	{
		if (c[j] == '-')
			_sign *= -1;

		if (c[j] >= '0' && c[j] <= '9')
		{
			_flag = 1;
			convresult *= 10;
			convresult += (c[j] - '0');
		}
		else if (_flag == 1)
			_flag = 2;
	}

	if (_sign == -1)
		_output = -convresult;
	else
		_output = convresult;

	return (_output);
}
