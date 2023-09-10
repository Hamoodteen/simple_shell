#include "shell.h"
/**
 * main - func
 * @argc: int
 * @argv: args
 * Return: 0 or 1
*/
int main(int argc, char **argv)
{
	char *s;
	size_t len;
	size_t lens;

	(void)argc;
	if (execve(argv[1], argv, NULL) == -1)
	{
		perror("Error:");
	}
	while (1)
	{
		len = lens = 0;
		s = NULL;
		_puts("$: ");
		if (getline(&s, &len, stdin) != -1)
		{
			if (strcmp(s, "exit\n") == 0)
			{
				free(s);
				exit(EXIT_SUCCESS);
			}
			fwrite(s, len, 1, stdout);
		}
		else
		{
			perror("Error !");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
