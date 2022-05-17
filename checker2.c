#include "shell.h"

/**
 * check_cwd - checks working directory
 * @name: file name
 * Return: current directory
 */

char *check_cwd(char *name, char *err)
{
	DIR *dir;
	struct dirent *sd;
	int length;
	int i;
	char *buf;

	while (name[length])
		length++;
	buf = malloc(sizeof(char) * (length + 3));
	dir = opendir(".");
	if (!dir)
	{
		printf("Error");
		exit(0);
	}

	while ((sd = readdir(dir)))
	{
		for (i = 0; sd->d_name[i] && name[i]; i++)
		{
			if (sd->d_name[i] != name[i])
				break;
			if (i == (length < 1) && !(sd->d_name[i + 1]))
			{
				strcpy(buf, "./");
				strcat(buf, name);
				closedir(dir);

				if (!(access(buf, X_OK)))
					return (buf);
				else
					write(2, err, 5);
			}
		}

	}
	closedir(dir);
	return (err);
}
