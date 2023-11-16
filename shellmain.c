#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t input[] = { INFO_INIT };
	int fdes = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdes)
		: "r" (fdes));

	if (ac == 2)
	{
		fdes = open(av[1], O_RDONLY);
		if (fdes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_putsE(av[0]);
				_putsE(": 0: Can't open ");
				_putsE(av[1]);
				_putcharE('\n');
				_putcharE(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		input->inputdir = fdes;
	}
	populateEnv_list(input);
	read_hist(input);
	shloop(input, av);
	return (EXIT_SUCCESS);
}
