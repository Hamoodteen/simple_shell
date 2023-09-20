#include "shell.h"

/**
 * initializer - call fork_process func and myexitenvcd func after
 * handling && || seperator
 * @commands: commads seperated by semicolon;
 * @argv: arg vector from main func
 * @env: environment from main func
 * @cnt: counter
 * Return: status
*/
int initializer(char **commands, char *argv[], char *env[], int cnt)
{
	char **oneCommand = NULL, *args[50];
	int i, j, ex_st = 0;

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
			ex_st = myexitenvcd(oneCommand[j], args, env, argv[0], cnt);
			if (ex_st == 2)
				break;
			if (ex_st != 0)
				ex_st = fork_process(oneCommand[j], args, env, argv[0], cnt);
		}
		free(oneCommand);
	}
	return (ex_st);
}

/**
 * main - the main func for simple shell(sh)
 * @argc: the number of arg vector
 * @argv: arg vector
 * @env: environment
 * Return: exit status
*/
int main(int argc, char *argv[], char *env[])
{
	char *s, **commands = NULL;
	size_t len;
	int i, whitespace, cnt = 0, a, fd = 0, st = 0;

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
			return (st); }
		removeNewline(s);
		removeComment(s);
		cnt++;
		whitespace = space(s, whitespace, i);
		if ((s[0] == '\0') || (whitespace))
		{
			free(s);
			continue; }
		commands = splitCommands(s, ";");
		st = initializer(commands, argv, env, cnt);
		free(commands);
		free(s); }
	return (0); }

/*
*for (i = 0; commands[i] != NULL; i++)
*{
*	tok(commands[i], args);
*	st = myexitenvcd(commands[i], args, env, argv[0], cnt);
*	if (st == 2)
*		break;
*	if (st != 0)
*		st = fork_process(commands[i], args, env, argv[0], cnt);
*}
*/
