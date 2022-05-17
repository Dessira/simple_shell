#include "shell.h"

/**
 * main - main shell function
 * @argc: number of arguments
 * @argv: arguments array
 * Return: 0
 */

void shell(int ac, char **av, char **env)
{
	char *command;
	char **args;
	int stat = 1;
	int i;
	char *name, *tmp = NULL;
	char *err = "Error";

	do{
		prompt();
		command = read_cmd();
		args = tokenize(command);
		i = bridge(args[0], args);

		if (i == 2)
		{
			name = args[0];
			args[0] = check_path(args[0], tmp, err); 
			if (args[0] == err)
			{
				args[0] = check_cwd(name, err);
				if (args[0] == name)
					write(1, err, 5);
			}
		}
		if (args[0] != err)
			stat = execute_cmd(args, command, env, i);
		free(command);
		free(args);

	}while (stat);
	if (!ac)
		(void)ac;
	if (!av)
		(void)av;
	if (!env)
		(void)env;
}
