#include "shell.h"

/**
 * main - func
 * @argc: int
 * @argv: args
 * Return: 0 or 1
*/
int main(int argc, char *argv[])
{
	char *args[50], *s;
	size_t len;
	int i;

	(void)argc;
	(void)argv;
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
			if (myexitenv(s, args) != -1)
				fork_process(s, args); }
		else
		{
			perror(s);
			exit(EXIT_FAILURE); }
	free(s); }
	return (0);
}
