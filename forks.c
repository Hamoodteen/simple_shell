#include "shell.h"

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
		ex = myexit(args, argv0, cnt);
		if (ex != 2)
			exit(ex);
		else
			return (2); }
	else if ((_strcmp(s, "env") == 0) || (_strcmp(s, "printenv") == 0))
	{
		ee = myenv(args, env, e);
		return (ee); }
	else if (_strcmp(s, "setenv") == 0)
	{
		if (_setenv(args[1], args[2], 1) != 0)
		{
			write(STDERR_FILENO, "Error\n", 7);
			return (2); }
		return (0); }
	else if (_strcmp(s, "unsetenv") == 0)
	{
		if (_unsetenv(args[1]) != 0)
		{
			write(STDERR_FILENO, "Error\n", 7);
			return (2); }
		return (0); }
	else if (_strcmp(s, "cd") == 0)
	{
		if (_strcmp(_cd(args, argv0, cnt), _getenv("HOME")) == 0)
			return (0);
		else
			return (2);
		(void)mycd;
		/* mycd = _cd(args, argv0, cnt); */
		/* write(STDIN_FILENO, mycd, _strlen(mycd)); */
	}
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
		write(STDERR_FILENO, inttostring(cnt), _strlen(inttostring(cnt)));
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
			write(STDERR_FILENO, inttostring(cnt), _strlen(inttostring(cnt)));
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
 * _cd - f
 * @newdir: char
 * @argv0: argv0
 * @cnt: int
 * Return: char
*/
char *_cd(char **newdir, char *argv0, int cnt)
{
	char *homedir = _getenv("HOME");
	char *oldpath;

	if (newdir[1] == NULL)
	{
		chdir(homedir);
		_setenv("PWD", homedir, 1);
		return (homedir); }
	if (_strcmp(newdir[1], "-") == 0)
	{
		oldpath = _getenv("PWD");
		chdir(oldpath);
		_setenv("PWD", oldpath, 1);
		return (oldpath);
	}
	else
	{
		if (chdir(newdir[1]) == 0)
		{
			_setenv("PWD", newdir[1], 1);
			return (newdir[1]);
		}
		else
		{
			oldpath = _getenv("PWD");
			write(STDERR_FILENO, argv0, _strlen(argv0));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, inttostring(cnt), _strlen(inttostring(cnt)));
			write(STDERR_FILENO, ": cd: can't cd to ", 18);
			write(STDERR_FILENO, newdir[1], _strlen(newdir[1]));
			write(STDERR_FILENO, "\n", 1);
			return (oldpath);
		}
	}
}

/**
 * filefd - f
 * @argv: argv
 * @fd: file
 * @env: env
 * @cnt: count
 * Return: int
*/
int filefd(char *argv[], int fd, char *env[], int cnt)
{
	char buffer[8192], *start, *end, *args[2];
	ssize_t bytes_read;
	int st;

	cnt = 1;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": 0: cannot open ", 17);
	write(STDERR_FILENO, argv[1], _strlen(argv[1]));
	write(STDERR_FILENO, ": No such file\n", 15);
	return (2); }
	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		start = end = buffer;
		while (end < buffer + bytes_read)
		{
			if (*end == '\n')
			{
				*end = '\0';
				if (_strlen(start) > 0)
				{
					args[0] = start;
					args[1] = NULL;
					st = initializer(args, argv, env, cnt);
					cnt++;
				}
				start = end + 1; }
			end++; }
		return (st);
	}
	if (close(fd) == -1)
		return (3);
	return (0);
}

/**
 * _fgetc - f
 * @stream: file
 * Return: int
*/
int _fgetc(FILE *stream)
{
	char c;
	int nread;

	nread = read(fileno(stream), &c, 1);
	if (nread == 0)
		return (EOF);
	return (c);
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
