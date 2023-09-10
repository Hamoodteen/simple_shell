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
	char *tok;
	char *args[50];
	size_t len;
	pid_t child;
	int i;
	int a;
	int ato;
	int status;

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
			tok = strtok(s, " ");
			while (tok != NULL)
			{
				args[i] = tok;
				tok = strtok(NULL, " ");
				i++;
			}
			args[i] = NULL;
			if (strcmp(s, "exit") == 0)
			{
				if (args[1] != NULL)
					ato = atoi(args[1]);
				free(s);
				exit(ato);
			}
			child = fork();
			if (child == -1)
            {
                perror("fork error");
                exit(EXIT_FAILURE);
            }
            if (child == 0)
            {
                if (execve(args[0], args, NULL) == -1)
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
