#include "shell.h"

/**
 * main - function that implements simple shell features
 * @argc: number of arguements
 * @argv: argument vector
 * @env: program environment
 *
 * Return: exit status
 */
int main(int argc, char *argv[], char *env[])
{
	char *s, **commands = NULL;
	size_t len;
	int i, whitespace, cnt = 0, a, fd = 0, st = 0;

	(void)argc;
	if (argv[1] != NULL)
	{
		a = filefd(argv, fd, env, cnt);
		return (a); }
	while (1)
	{
		len = i = 0;
		s = NULL;
		write(STDIN_FILENO, "~$: ", 5);
		if (_getline(&s, &len, stdin) == -1)
		{
			free(s);
			return (st); }
		removeNewline(s);
		removeComment(s);
		cnt++;
		whitespace = space(s, whitespace, i);
		if ((s[0] == '\0') || (whitespace))
		{
			free(s);
			continue; }
		commands = splitCommands(s, ";");
		st = initializer(commands, argv, env, cnt);
		free(commands);
		free(s); }
	return (0); }
