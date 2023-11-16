#include "shell.h"

/**
 **_mymemset - fills memory with a constant byte
 *@ptr: the pointer to the memory area
 *@bt: the byte to fill *ptr with
 *@numb: the amount of bytes to be filled
 *Return: (ptr) a pointer to the memory area ptr
 */
char *_mymemset(char *ptr, char bt, unsigned int numb)
{
	unsigned int j;

	for (j = 0; j < numb; j++)
		ptr[j] = bt;
	return (ptr);
}

/**
 * freestr - frees a string of strings
 * @_pp: string of strings
 */
void freestr(char **_pp)
{
	char **b = _pp;

	if (!_pp)
		return;
	while (*_pp)
		free(*_pp++);
	free(b);
}

/**
 * _reallocmem - reallocates a block of memory
 * @_ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_reallocmem(void *_ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;

	if (!_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(_ptr), NULL);
	if (new_size == old_size)
		return (_ptr);

	s = malloc(new_size);
	if (!s)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		s[old_size] = ((char *)_ptr)[old_size];
	free(_ptr);
	return (s);
}
