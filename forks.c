#include "shell.h"

/**
 * tok - tokanization for the args
 * @s: the user input
 * @args: like {'/bin/ls', '-la'}
*/
void tok(char *s, char *args[])
{
	int a, i = 0;
	char *tok;

	for (a = 0; a < 50; a++)
		args[a] = NULL;
	tok = _strtok(s, " ");
	while (tok != NULL)
	{
		args[i] = tok;
		tok = _strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
}

/**
 * myexitenv - exit command handle
 * @s: the user input
 * @args: like {'/bin/ls', '-la'}
 * @env: environment variables
 * @argv0: argv0
 * @cnt: count
 * Return: 1 if no exit or on print env, -1 to many arguments,
 * or no return(exit) on success exit
*/
int myexitenv(char *s, char *args[], char *env[], char *argv0, int cnt)
{
	int ato, e;

	ato = 0;
	e = 0;
	if (_strcmp(s, "exit") == 0)
	{
		if (args[1] != NULL)
		{
			ato = _atoi(args[1]);
			if ((*args[1] < '0') || (*args[1] > '9'))
			{
				write(STDERR_FILENO, argv0, sizeof(argv0) - 3);
				write(STDERR_FILENO, ": ", 2);
				write(STDERR_FILENO, inttostring(cnt), (sizeof(cnt) / 4));
				write(STDERR_FILENO, ": exit: Illegal number: ", 24);
				if ((ato < 0))
					write(STDERR_FILENO, args[1], sizeof(args[1]) - 5);
				else
					write(STDERR_FILENO, args[1], sizeof(args[1]) - 4);
				write(STDERR_FILENO, "\n", 1);
				exit(2); }
			else if ((*args[1] > '0') || (*args[1] < '9'))
				exit(ato);
		}
		else
			exit(EXIT_SUCCESS); }
	else if ((_strcmp(s, "env") == 0) || (_strcmp(s, "printenv") == 0))
	{
		if (args[1] == NULL)
		{
			for (e = 0; env[e] != NULL; e++)
			{
				_puts(env[e]);
				_putchar('\n'); }
		}
	}
	return (1); }

/**
 * fork_process - fork (new process)
 * @s: the user input
 * @args: like {'/bin/ls', '-la'}
 * @env: env
 * @cnt: count
 * @argv0: argv0
*/
void fork_process(char *s, char *args[], char *env[], char *argv0, int cnt)
{
	pid_t child;
	int status;
	char *command_path = _which(args[0]);

	if (command_path == NULL)
	{
		write(STDERR_FILENO, argv0, sizeof(argv0) - 3);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, inttostring(cnt), (sizeof(cnt) / 4));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, args[0], sizeof(args[0]) - 4);
		perror(args[0]);
		return; }
	child = fork();
	if (child == -1)
	{
		perror(s);
		exit(EXIT_FAILURE); }
	else if (child == 0)
	{
		if (_strcmp(s, "$$") == 0)
		{
			child = getpid();
			print_number(child);
			_putchar('\n'); }
		else if (_strcmp(s, "$?") == 0)
		{
			print_number(WEXITSTATUS(status));
			_putchar('\n'); }
		else if (execve(command_path, args, env) == -1)
		{
			write(STDERR_FILENO, argv0, sizeof(argv0) - 3);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, inttostring(cnt), (sizeof(cnt) / 4));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, args[0], sizeof(args[0]) - 4);
			perror(args[0]);
			exit(EXIT_FAILURE); }
	}
	else
		waitpid(child, &status, 0); }
