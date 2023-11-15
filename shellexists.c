#include "shell.h"

/**
 **_mystrncpy - copies a string
 *@loci: the destination string to be copied to
 *@s: the source string
 *@numb: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_mystrncpy(char *loci, char *s, int numb)
{
	int i, j;
	char *c = loci;

	i = 0;
	while (s[i] != '\0' && i < numb - 1)
	{
		loci[i] = s[i];
		i++;
	}
	if (i < numb)
	{
		j = i;
		while (j < numb)
		{
			loci[j] = '\0';
			j++;
		}
	}
	return (c);
}

/**
 **_strnconcat - concatenates two strings
 *@loci: the first string
 *@s: the second string
 *@numb: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strnconcat(char *loci, char *s, int numb)
{
	int i, j;
	char *c = loci;

	i = 0;
	j = 0;
	while (loci[i] != '\0')
		i++;
	while (s[j] != '\0' && j < numb)
	{
		loci[i] = s[j];
		i++;
		j++;
	}
	if (j < numb)
		loci[i] = '\0';
	return (s);
}

/**
 **_mystrchr - locates a character in a string
 *@str: the string to be parsed
 *@h: the character to look for
 *Return: (str) a pointer to the memory area str
 */
char *_mystrchr(char *str, char h)
{
	do {
		if (*str == h)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
