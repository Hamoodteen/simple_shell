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
	int i, whitespace, cnt = 0;

	(void)argc;
	if (argv[1] != NULL)
	{
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": 0: cannot open ", 17);
		write(STDERR_FILENO, argv[1], _strlen(argv[1]));
		write(STDERR_FILENO, ": No such file\n", 15);
		exit(2); }
	while (1)
	{
		len = i = 0;
		s = NULL;
		write(STDIN_FILENO, "$: ", 4);
		if (_getline(&s, &len, stdin) != -1)
		{
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
			tok(s, args);
			if (myexitenv(s, args, env, argv[0], cnt) != -1)
				fork_process(s, args, env, argv[0], cnt); }
		else
			exit(EXIT_SUCCESS);
	free(s); }
	return (0); }
