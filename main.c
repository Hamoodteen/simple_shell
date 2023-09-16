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
	int i, cnt = 0;

	(void)argc;
	if (argv[1] != NULL)
	{
		_puts(argv[0]);
		_puts(": 0: cannot open ");
		_puts(argv[1]);
		_puts(": No such file\n");
		return (1);
	}
	while (1)
	{
		len = i = 0;
		s = NULL;
		_puts("$: ");
		if (_getline(&s, &len, stdin) != -1)
		{
			s[_strcspn(s, "\n")] = '\0';
			if (s[0] == '\0')
			{
				free(s);
				continue; }
			tok(s, args);
			cnt++;
			if (myexitenv(s, args, env, argv[0], cnt) != -1)
				fork_process(s, args, env, argv[0], cnt); }
		else
		{
			perror(s);
			exit(EXIT_FAILURE); }
	free(s); }
	return (0); }
