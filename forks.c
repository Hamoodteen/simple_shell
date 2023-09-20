#include "shell.h"

/**
 * tok - tokanization for the args and convert s to s[0] only like
 * s = "/bin/ls -la" to s = "/bin/ls"
 * @s: the user input like "/bin/ls -la"
 * @args: return like {'/bin/ls', '-la'}
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
 * myexitenvcd - command handle
 * @s: the user input
 * @args: like {'/bin/ls', '-la'}
 * @env: environment variables
 * @argv0: argv0
 * @cnt: count
 * Return: int
*/
int myexitenvcd(char *s, char *args[], char *env[], char *argv0, int cnt)
{
	int ee, e = 0, ex = 0;
	char *mycd;

	if (_strcmp(s, "exit") == 0)
	{
		ex = _myexit(args, argv0, cnt);
		if (ex != 2)
			exit(ex);
		else
			return (0); }
	else if ((_strcmp(s, "env") == 0) || (_strcmp(s, "printenv") == 0))
	{
		ee = myenv(args, env, e);
		return (ee); }
	else if (_strcmp(s, "setenv") == 0)
	{
		if (_setenv(args[1], args[2], 1) != 0)
			write(STDERR_FILENO, "Error\n", 7);
		return (-1); }
	else if (_strcmp(s, "unsetenv") == 0)
	{
		if (_unsetenv(args[1]) != 0)
			write(STDERR_FILENO, "Error\n", 7);
		return (-1); }
	else if (_strcmp(s, "cd") == 0)
	{
		_cd(args, argv0, cnt);
		(void)mycd;
		/* mycd = _cd(args, argv0, cnt); */
		/* write(STDIN_FILENO, mycd, _strlen(mycd)); */
		return (-1); }
	return (1); }

/**
 * fork_process - fork (new process)
 * @s: the user input
 * @args: like {'/bin/ls', '-la'}
 * @env: env
 * @cnt: count
 * @argv0: argv0
 * Return: statues
*/
int fork_process(char *s, char *args[], char *env[], char *argv0, int cnt)
{
	pid_t child;
	int status, exit_status = 0;
	char *command_path = _which(args[0]);

	if (command_path == NULL)
	{
		write(STDERR_FILENO, argv0, _strlen(argv0));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, inttostring(cnt), (sizeof(cnt) / 4));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, args[0], _strlen(args[0]));
		write(STDERR_FILENO, ": not found\n", 12);
		return (127); }
	child = fork();
	if (child == -1)
	{
		perror(s);
		return (1); }
	else if (child == 0)
	{
		if (execve(command_path, args, env) == -1)
		{
			write(STDERR_FILENO, argv0, _strlen(argv0));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, inttostring(cnt), (sizeof(cnt) / 4));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, args[0], _strlen(args[0]));
			perror(args[0]);
			free(command_path);
			return (1); }
	}
	else
	{
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status); }
	}
	return (exit_status); }

/**
 * filefd - f
 * @argv: argv
 * @fd: file
 * @env: env
 * Return: int
*/
int filefd(char *argv[], int fd, char *env[])
{
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": 0: cannot open ", 17);
	write(STDERR_FILENO, argv[1], _strlen(argv[1]));
	write(STDERR_FILENO, ": No such file\n", 15);
	return (2); }
	if (execve(argv[1], argv, env) == -1)
		return (2);
	if (close(fd) == -1)
		return (3);
	return (0);
}

/**
 * _myexit - f
 * @args: char
 * @argv0: char
 * @cnt: int
 * Return: int
*/
int _myexit(char **args, char *argv0, int cnt)
{
	int ato = 0;

	if (args[1] != NULL)
	{
		ato = _atoi(args[1]);
		if ((*args[1] < '0') || (*args[1] > '9'))
		{
			write(STDERR_FILENO, argv0, _strlen(argv0));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, inttostring(cnt), (sizeof(cnt) / 4));
			write(STDERR_FILENO, ": exit: Illegal number: ", 24);
			write(STDERR_FILENO, args[1], _strlen(args[1]));
			write(STDERR_FILENO, "\n", 1);
			return (2); }
		else if ((*args[1] > '0') || (*args[1] < '9'))
			return (ato);
	}
	return (0);
}

/**
* ignore_code - here
*	if (_strcmp(s, "$$") == 0)
*	{
*		child = getpid();
*		print_number(child);
*		_putchar('\n'); }
*	else if (_strcmp(s, "$?") == 0)
*	{
*		print_number(WEXITSTATUS(status));
*		_putchar('\n'); }
*	if ((_strcmp(command, "$$") == 0) || (_strcmp(command, "$?") == 0))
*		return (command);
*/
