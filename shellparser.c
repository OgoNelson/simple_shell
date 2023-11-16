#include "shell.h"

/**
* exec_cmd - determines if a file is an executable command
 * @data: the info struct
 * @loci: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int exec_cmd(info_t *data, char *loci)
{
	struct stat _st;

	(void)data;
	if (!loci || stat(loci, &_st))
		return (0);

	if (_st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupli_chars - duplicates characters
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dupli_chars(char *path_str, int start, int stop)
{
	static char buffer[1024];
	int j = 0, l = 0;

	for (l = 0, j = start; j < stop; j++)
		if (path_str[j] != ':')
			buffer[l++] = path_str[j];
	buffer[l] = 0;
	return (buffer);
}

/**
 * find_cmd - finds the cmd in the PATH string
 * @data: the info struct
 * @path_str: the PATH string
 * @_cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_cmd(info_t *data, char *path_str, char *_cmd)
{
	int j = 0, curr_posi = 0;
	char *_path;

	if (!path_str)
		return (NULL);
	if ((_mystrlen(_cmd) > 2) && startstr(_cmd, "./"))
	{
		if (exec_cmd(data, _cmd))
			return (_cmd);
	}
	while (1)
	{
		if (!path_str[j] || path_str[j] == ':')
		{
			_path = dupli_chars(path_str, curr_posi, j);
			if (!*_path)
				_strconcat(_path, _cmd);
			else
			{
				_strconcat(_path, "/");
				_strconcat(_path, _cmd);
			}
			if (exec_cmd(data, _path))
				return (_path);
			if (!path_str[j])
				break;
			curr_posi = j;
		}
		j++;
	}
	return (NULL);
}
