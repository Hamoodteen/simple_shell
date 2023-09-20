#include "shell.h"

/**
 * main - the main func for simple shell(sh)
 * @argc: the number of arg vector
 * @argv: arg vector
 * @env: environment
 * Return: exit status 0 or 1
*/
int main(int argc, char *argv[], char *env[])
{
	char *s, **commands = NULL;
	size_t len;
	int i, whitespace, cnt = 0, a, fd = 0;

	(void)argc;
	if (argv[1] != NULL)
	{
		a = filefd(argv, fd, env);
		return (a); }
	while (1)
	{
		len = i = 0;
		s = NULL;
		write(STDIN_FILENO, "~$: ", 5);
		if (_getline(&s, &len, stdin) == -1)
		{
			free(s);
			exit(2); }
		removeNewline(s);
		removeComment(s);
		cnt++;
		whitespace = space(s, whitespace, i);
		if ((s[0] == '\0') || (whitespace))
		{
			free(s);
			continue; }
		commands = splitCommands(s, ";");
		initializer(commands, argv, env, cnt);
		free(commands);
		free(s);
	}
	return (0); }
