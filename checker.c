#include "shell.h"

/**
 * read_cmd - reads user input
 * Return: pointer
 */

char *read_cmd(void)
{
	int i;
	char *command = NULL;
	size_t size = 0;

	i = getline(&command, &size, stdin);

	if (i == EOF)
	{
		if (isatty(STDIN_FILENO))
		{
			write(1, "\n", 1);
		}
		exit(0);
	}
	return (command);
}
/**
 * tokenize - assigns tokens and split cmd
 * @command: input command
 * Return: tokenized string
 */

char **tokenize(char *command)
{
	size_t bufsize = TOKENS_BUFFER_SIZE;
	char *token;
	char **tokens = malloc(sizeof(char *) * bufsize);
	int i = 0;

	if (!tokens)
	{
		perror("Error");
		exit(0);
	}
	token = strtok(command, TOKEN_DELIMITERS);
	while (token)
	{
		tokens[i] = token;
		token = strtok(NULL, TOKEN_DELIMITERS);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
/**
 * check_builtin - checks if command is builtin
 * @args: arguments
 * @command: buffer containing command
 * @env: environment
 * Return: 1 or 0
 */
int check_builtin(char **args, char *command, char **env)
{
	builtins_t list[] = {
		{"exit", exit_shell},
		{"env", env_shell},
		{NULL, NULL}
	};
	int i;

	for (i = 0; list[i].arg != NULL; i++)
	{
		if (_strcmp(list[i].arg, args[0]) == 0)
		{
			list[i].builtin(args, command, env);
			return (1);
		}
	}
	return (0);
}
/**
 * execute - executes command
 * @args: arguments
 * Return: 1
 */
int execute(char **args)
{
	pid_t child, parent;
	int stat;

	child = fork();
	if (child == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error");
			exit(0);
		}
		else if (child < 0)
		{
			perror("Error");
			exit(0);
		}
		else
			do{
				parent = waitpid(child, &stat, WUNTRACED);
			}while (!WIFEXITED(stat) && WIFSIGNALED(stat));
	}
	(void)parent;
	return (1);
}
/**
 * builtin_finder - finds builtins
 * @args: arguments
 * Return: 1 or 0
 */
int builtin_finder(char **args)
{
	int i;
	builtins_t list[] = {
		{"exit", exit_shell},
		{"env", env_shell},
		{NULL, NULL}
	};
	for (i = 0; list[i].arg != NULL; i++)
	{
		if (_strcmp(list[i].arg, args[0]) == 0)
			return (1);
	}
	return (0);
}
