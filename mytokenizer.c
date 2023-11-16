#include "shell.h"

/**
 * **strtowrd - splits a string into words. Repeat delimiters are ignored
 * @s: the input string
 * @delim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtowrd(char *s, char *delim)
{
	int i, j, k, m, numofwords = 0;
	char **c;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!my_delim(s[i], delim) && (my_delim(s[i + 1], delim) || !s[i + 1]))
			numofwords++;

	if (numofwords == 0)
		return (NULL);
	c = malloc((1 + numofwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < numofwords; j++)
	{
		while (my_delim(s[i], delim))
			i++;
		k = 0;
		while (!my_delim(s[i + k], delim) && s[i + k])
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			c[j][m] = s[i++];
		c[j][m] = 0;
	}
	c[j] = NULL;
	return (c);
}

/**
 * **strtowrd2 - splits a string into words
 * @s: the input string
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtowrd2(char *s, char delim)
{
	int i, j, k, m, numofwords = 0;
	char **c;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != delim && s[i + 1] == delim) ||
		    (s[i] != delim && !s[i + 1]) || s[i + 1] == delim)
			numofwords++;
	if (numofwords == 0)
		return (NULL);
	c = malloc((1 + numofwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, j = 0; j < numofwords; j++)
	{
		while (s[i] == delim && s[i] != delim)
			i++;
		k = 0;
		while (s[i + k] != delim && s[i + k] && s[i + k] != delim)
			k++;
		c[j] = malloc((k + 1) * sizeof(char));
		if (!c[j])
		{
			for (k = 0; k < j; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			c[j][m] = s[i++];
		c[j][m] = 0;
	}
	c[j] = NULL;
	return (c);
}
