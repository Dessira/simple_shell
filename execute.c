#include "shell.h"

/**
 * execute_cmd - executes command
 * @args: arguments
 * @command: command input
 * @env: environ
 * @i: selects code
 * Return: 1
 */
int execute_cmd(char **args, char *command, char **env, int i)
{
	int stat;

	if (args[0] == NULL)
		return (1);
	if (i == 1)
	{
		if (check_builtin(args, command, env) == 1)
			return (1);
	}
	stat = execute(args);
	return (stat);
}
