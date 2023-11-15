#include "shell.h"

/**
 * _strtoint - converts a string to an int
 * @c: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _strtoint(char *c)
{
	int j = 0;
	unsigned long int _result = 0;

	if (*c == '+')
		c++;  /* TODO: why does this make main return 255? */
	for (j = 0;  c[j] != '\0'; j++)
	{
		if (c[j] >= '0' && c[j] <= '9')
		{
			_result *= 10;
			_result += (c[j] - '0');
			if (_result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (_result);
}

/**
 * print_E - prints an error message
 * @data: the parameter & return info struct
 * @errorstr: string of specified error type
 * Return: converted number otherwise 0
 *        -1 on error
 */
void print_E(info_t *data, char *errorstr)
{
	_putsE(data->filename);
	_putsE(": ");
	print_deci(data->linecount, STDERR_FILENO);
	_putsE(": ");
	_putsE(data->argv[0]);
	_putsE(": ");
	_putsE(errorstr);
}

/**
 * print_deci - function prints a decimal (integer) number (base 10)
 * @numb: the input
 * @fdes: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_deci(int numb, int fdes)
{
	int (*__myputchar)(char) = _myputchar;
	int j, _count = 0;
	unsigned int _abs, _current;

	if (fdes == STDERR_FILENO)
		__myputchar = _putcharE;
	if (numb < 0)
	{
		_abs = -numb;
		__myputchar('-');
		_count++;
	}
	else
		_abs = numb;
	_current = _abs;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs / j)
		{
			__myputchar('0' + _current / j);
			_count++;
		}
		_current %= j;
	}
	__myputchar('0' + _current);
	_count++;

	return (_count);
}

/**
 * convertnumb - converter function
 * @numb: number
 * @_base: base
 * @_flags: argument flags
 *
 * Return: string
 */
char *convertnumb(long int numb, int _base, int _flags)
{
	static char *_array;
	static char _buffer[50];
	char _sign = 0;
	char *_ptr;
	unsigned long m = num;

	if (!(_flags & CONVERT_UNSIGNED) && numb < 0)
	{
		m = -numb;
		_sign = '-';

	}
	_array = _flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	_ptr = &_buffer[49];
	*_ptr = '\0';

	do	{
		*--_ptr = _array[m % _base];
		m /= _base;
	} while (m != 0);

	if (_sign)
		*--_ptr = _sign;
	return (_ptr);
}

/**
 * rm_comments - function replaces first instance of '#' with '\0'
 * @b: address of the string to modify
 *
 * Return: Always 0;
 */
void rm_comments(char *b)
{
	int j;

	for (j = 0; b[j] != '\0'; j++)
		if (b[j] == '#' && (!j || b[j - 1] == ' '))
		{
			b[j] = '\0';
			break;
		}
}
