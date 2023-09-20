#include "shell.h"

/**
 * main - the main func for simple shell(sh)
 * @argc: the number of arg vector
 * @argv: arg vector
 * @env: environment
 * Return: exit status
*/
int main(int argc, char *argv[], char *env[])
{
	char *s, *args[50], **commands = NULL;
	size_t len;
	int i, whitespace, cnt = 0, a, fd = 0, st = 0;

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
		for (i = 0; commands[i] != NULL; i++)
		{
			tok(commands[i], args);
			st = myexitenvcd(commands[i], args, env, argv[0], cnt);
			if (st == 2)
			{
				st = 2;
				break; }
			if (st != 0)
				st = fork_process(commands[i], args, env, argv[0], cnt);
		}
		free(commands);
		free(s);
	}
	return (0); }
