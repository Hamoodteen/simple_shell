#include "shell.h"

void initarg(char *args[])
{
	int i;
	for (i = 0; i < 50; i++)
		args[i] = NULL;
}

void child_process(char *s, char *args[])
{
	pid_t child = fork();
	int status;
	int e;
	int ato = 0;

	if (_strcmp(s, "exit") == 0)
	{
		if (args[1] != NULL)
			ato = _atoi(args[1]);
		free(s);
		exit(ato);
	}
	if (child == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if (child == 0)
	{
		args[0] = get_location(args[0]);
		if (_strcmp(s, "env") == 0)
		{
			for (e = 0; environ[e] != NULL; e++)
			{
				_puts(environ[e]);
				_putchar('\n');
			}
		}
		else if (_strcmp(s, "$$") == 0)
		{
			child = getpid();
			print_number(child);
			_putchar('\n');
		}
		else if (_strcmp(s, "$?") == 0)
		{
			print_number(WEXITSTATUS(status));
			_putchar('\n');
		}
		else if (execve(args[0], args, environ) == -1)
		{
			perror("execute error");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(child, &status, 0);
}

int main(int argc, char *argv[])
{
	char *s;
	char *args[50];
	size_t len;
	int i;
	char *tok;

	(void)argc;
	(void)argv;
	while (1)
	{
		len = i = 0;
		s = NULL;
		initarg(args);

		_puts("$: ");
		if (getline(&s, &len, stdin) != -1)
		{
			s[_strcspn(s, "\n")] = '\0';
			if (s[0] == '\0')
			{
				free(s);
				continue;
			}

			tok = strtok(s, " ");
			while (tok != NULL)
			{
				args[i] = tok;
				tok = strtok(NULL, " ");
				i++;
			}
			args[i] = NULL;

			child_process(s, args);
		}
		else
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		free(s);
	}
	return (0);
}
