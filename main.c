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
	char PATH[50] = "/bin/";
	char pathtemp[50];
	char *args[50];
	char *tok;
	size_t len;
	pid_t child;
	int i;
	int a;
	int ato;
	int status;
	int e;

	for (a = 0; a < 50; a++)
		args[a] = NULL;
	(void)argc;
	(void)argv;
	while (1)
	{
		len = status = i = ato = 0;
		s = NULL;
		_puts("$: ");
		if (getline(&s, &len, stdin) != -1)
		{
			s[strcspn(s, "\n")] = '\0';
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
			memcpy(pathtemp, PATH, (_strlen(PATH) + 1));
			if (strncmp(args[0], pathtemp, (_strlen(pathtemp))) != 0)
			{
				strcat(pathtemp, args[0]);
				args[0] = pathtemp;
			}
			child = fork();
			if (strcmp(s, "exit") == 0)
			{
				if (args[1] != NULL)
					ato = atoi(args[1]);
				free(s);
				exit(ato);
			}
			if (child == -1)
			{
				perror("fork error");
				exit(EXIT_FAILURE);
			}
			if (child == 0)
			{
				if (strcmp(s, "env") == 0)
				{
					for (e = 0; environ[e] != NULL; e++)
					{
						_puts(environ[e]);
						_putchar('\n');
					}
				}
				else if (strcmp(s, "$$") == 0)
				{
					child = getpid();
					print_number(child);
					_putchar('\n');
				}
				else if (strcmp(s, "$?") == 0)
				{
					print_number(WIFEXITED(status));
					_putchar('\n');
				}
				else if (execve(args[0], args, NULL) == -1)
				{
					perror("execute error");
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
				}
			else
				waitpid(child, &status, 0);
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
