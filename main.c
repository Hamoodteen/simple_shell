#include "shell.h"

/**
 * tokAndExit - tokanization for the args
 * @s: the user input
 * @args: like {'/bin/ls', '-la'}
*/
void tokAndExit(char *s, char *args[])
{
	int a, i = 0, ato = 0;
	char *tok;

	for (a = 0; a < 50; a++)
		args[a] = NULL;

	tok = strtok(s, " ");
	while (tok != NULL)
	{
		args[i] = tok;
		tok = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	if (_strcmp(s, "exit") == 0)
	{
		if (args[1] != NULL)
			ato = _atoi(args[1]);
		free(s);
		exit(ato); }
}

/**
 * fork_process - fork (new process)
 * @s: the user input
 * @args: like {'/bin/ls', '-la'}
*/
void fork_process(char *s, char *args[])
{
	pid_t child;
	int status, e;

	args[0] = get_location(args[0]);
	if ((args[0]) == NULL)
	{
		perror(s);
		return;
	}
	child = fork();
	if (child == -1)
	{
		perror(s);
		exit(EXIT_FAILURE); }
	else if (child == 0)
	{
		if (_strcmp(s, "env") == 0)
		{
			for (e = 0; environ[e] != NULL; e++)
			{
				_puts(environ[e]);
				_putchar('\n'); }
		}
		else if (_strcmp(s, "$$") == 0)
		{
			child = getpid();
			print_number(child);
			_putchar('\n'); }
		else if (_strcmp(s, "$?") == 0)
		{
			print_number(WEXITSTATUS(status));
			_putchar('\n'); }
		else if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE); }
	}
	else
		waitpid(child, &status, 0);
}

/**
 * main - func
 * @argc: int
 * @argv: args
 * Return: 0 or 1
*/
int main(int argc, char *argv[])
{
	char *args[50], *s;
	size_t len;
	int i;

	(void)argc;
	(void)argv;
	while (1)
	{
		len = i = 0;
		s = NULL;
		_puts("$: ");
		if (getline(&s, &len, stdin) != -1)
		{
			s[_strcspn(s, "\n")] = '\0';
			if (s[0] == '\0')
			{
				free(s);
				continue; }
			tokAndExit(s, args);
			fork_process(s, args); }
		else
		{
			perror(s);
			exit(EXIT_FAILURE); }
	free(s); }
	return (0);
}
