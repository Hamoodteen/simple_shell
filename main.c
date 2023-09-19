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
	char *args[50], *s, **commands = NULL, **oneCommand = NULL;
	size_t len;
	int i, j, whitespace, cnt = 0, a, fd = 0;

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
			exit(EXIT_SUCCESS); }
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
			oneCommand = (char **)commands[i];
			if (check_substring(commands[i], "&&") == 1)
			{
				oneCommand = splitCommands(commands[i], "&&"); }
			else if (check_substring(commands[i], "||") == 1)
			{
				oneCommand = splitCommands(commands[i], "||"); }
			else
			{
				oneCommand = splitCommands(commands[i], ""); }
			for (j = 0; oneCommand[j] != NULL; j++)
			{
				tok(oneCommand[j], args);
				if (myexitenvcd(oneCommand[j], args, env, argv[0], cnt) != -1)
					fork_process(oneCommand[j], args, env, argv[0], cnt); }
			free(oneCommand); }
		free(commands);
		free(s);
	}
	return (0); }
