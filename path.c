#include "shell.h"

/**
 * check_path - finds the path
 * @name: name of file
 * @tmp: stores path
 * @err: error
 * Return: path or error
 */
char *check_path(char *name, char *tmp, char *err)
{
	DIR *dir;
	struct dirent *sd;
	char *f_path, *path, *buf;
	int len = 0;

	while (name[len])
		len++;
	path = _getenv("PATH");
	tmp = store_path(tmp, path);
	f_path = strtok(tmp, ":");

	while (f_path)
	{
		dir = opendir(f_path);
		if (!dir)
		{
			printf("Error");
			exit(0);
		}
		while ((sd = readdir(dir)))
		{
			buf = _readdir(err, sd, name, len, f_path, tmp);
			if (buf != err)
			{
				closedir(dir);
				if (!(access(buf, X_OK)))
					return (buf);
			}
		}

		closedir(dir);
		f_path = strtok(NULL, ":");
	}

	path = NULL;
	free(tmp);
	return (err);
}
/**
 * _readdir - reads dirctory file names
 *  @err: error
 *  @s: struct
 *  @name: file name
 *  @fp: file path
 *  @tmp: contains path variable
 *  @len: length of file name
 *  Return: path of file or error
 */
char *_readdir(char *err, struct dirent *s, char *name, int len, char *fp, char *tmp)
{
	char *buf;
	int i = 0;

	for (i = 0; s->d_name[i] && name[i]; i++)
	{
		if (s->d_name[i] != name[i])
			break;

		if (i == (len - 1) && !(s->d_name[i + 1]))
		{
			buf = strcat(fp, "/");
			buf = strcat(buf, name);
		       free(tmp);
	       return (buf);
		}
	}
	return (err);
}
/**
 * store_path - stores path string
 * @tmp: copy
 * @org: original path string
 * Return: tmp, org, or err
 */
char *store_path(char *tmp, char *org)
{
	int i = 0;

	if (!tmp)
	{
		tmp = malloc(sizeof(char) * 100);
		while (org[i])
		{
			tmp[i] = org[i];
				i++;
				tmp[i] = '\0';
		}
		i = 0;
		return (tmp);
	}
	else
	{
		while (tmp[i])
		{
			org[i] = tmp[i];
			i++;
			org[i] = '\0';
		}
		i = 0;
		return (org);
	}
	return ("Error");
}
