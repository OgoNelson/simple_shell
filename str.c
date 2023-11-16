#include "shell.h"

/**
 * _mystrlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int _mystrlen(char *str)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str++)
		j++;
	return (j);
}

/**
 * _mystrcomp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int _mystrcomp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * startstr - checks if _needle starts with _haystack
 * @_haystack: string to search
 * @_needle: the substring to find
 *
 * Return: address of next char of _haystack or NULL
 */
char *startstr(const char *_haystack, const char *_needle)
{
	while (*_needle)
		if (*_needle++ != *_haystack++)
			return (NULL);
	return ((char *)_haystack);
}

/**
 * _strconcat - concatenates two strings
 * @destbuf: the destination buffer
 * @srcbuf: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strconcat(char *destbuf, char *srcbuf)
{
	char *_ret = destbuf;

	while (*destbuf)
		destbuf++;
	while (*srcbuf)
		*destbuf++ = *srcbuf++;
	*destbuf = *srcbuf;
	return (_ret);
}
