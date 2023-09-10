#include "shell.h"
/**
 * main - func
 * @argc: int
 * @argv: args
 * Return: 0 or 1
*/
int main(int argc, char *argv[])
{
	char *s;
	char *path;
	char *ev[1];
	size_t len;

	(void)ev;
	ev[0] = "PATH=/bin:/usr/bin";
	ev[1] = NULL;
	path = "/usr/bin/";
	(void)argc;
	(void)argv;
	while (1)
	{
		len = 0;
		s = NULL;
		_puts("$: ");
		if (getline(&s, &len, stdin) != -1)
		{
			if (strcmp(s, "exit\n") == 0)
			{
				free(s);
				exit(EXIT_SUCCESS);
			}
			if (execve(path, &s, ev) == -1)
			{
				perror("Error");
			}
		}
		else
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
