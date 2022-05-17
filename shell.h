#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define TOKENS_BUFFER_SIZE 64
#define LINE_SIZE 1024
#define TOKEN_DELIMITERS " \t\r\n\a"
extern char **environ;

typedef struct builtins
{
	char *arg;
	void (*builtin)(char **args, char *line, char **env);
} builtins_t;

void prompt(void);
int builtin_finder(char **args);
int execute(char **args);
int check_builtin(char **args, char *command, char **env);
char **tokenize(char *command);
char *read_cmd(void);
int bridge(char *check, char **args);
char *store_path(char *tmp, char *org);
char *_readdir(char *err, struct dirent *s, char *name, int len, char *fp, char *tmp);
char *check_path(char *name, char *tmp, char *err);
int _strcmp(char *s1, char *s2);
char *_strstr(char *haystack, char *needle);
int _strlen(char *s);
void exit_shell(char **args, char *line, char **env);
void env_shell(char **args, char *line, char **env);
char *_getenv(char *env);
char *check_cwd(char *name, char *err);
int execute_cmd(char **args, char *command, char **env, int i);
void shell(int ac, char **av, char **env);
