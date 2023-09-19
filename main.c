#include "shell.h"

/**
 * main - func
 * @argc: int
 * @argv: args
 * @env: env
 * Return: 0 or 1
*/
int main(int argc, char *argv[], char *env[])
{
	char *args[50], *s;
	size_t len;
	int i, whitespace, cnt = 0, a, fd = 0;
	char **commands = NULL;

	(void)argc;
	if (argv[1] != NULL)
	{
		a = filefd(argv, fd, env);
		return (a); }
	while (1)
	{
		len = i = 0;
		s = NULL;
		write(STDIN_FILENO, "$: ", 4);
		if (_getline(&s, &len, stdin) == -1)
		{
			free(s);
			exit(EXIT_SUCCESS); }
		removeNewline(s);
		removeComment(s);
		s[_strcspn(s, "\n")] = '\0';
		cnt++;
		whitespace = 1;
		for (i = 0; s[i] != '\0'; i++)
		{
			if ((unsigned char)s[i] != ' ')
			{
				whitespace = 0;
				break; }
		}
		if ((s[0] == '\0') || (whitespace))
		{
			free(s);
			continue; }
		commands = splitCommands(s);
		for (i = 0; commands[i] != NULL; i++)
		{
			tok(commands[i], args);
			if (myexitenv(commands[i], args, env, argv[0], cnt) != -1)
				fork_process(commands[i], args, env, argv[0], cnt);
		}
	}
	free(s);
	return (0); }
