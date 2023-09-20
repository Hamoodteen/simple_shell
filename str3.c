#include "shell.h"

/**
 * check_substring - check if substring exists in string
 * @str: the string
 * @substring: the substring
 * Return: 1 if the substring exists in string
 * or 0 if the substring doesn't exist in string
*/
int check_substring(char *str, char *substring)
{
	int i;

	for (i = 0; i < (int)_strlen(str) - (int)_strlen(substring) + 1; i++)
	{
		if (_strncmp(str + i, substring, _strlen(substring)) == 0)
		{
		return (1);
		}
	}
	return (0);
}

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
	int i, j, exit_status = 0;

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
			if ((exit_status = myexitenvcd(oneCommand[j], args, env, argv[0], cnt)) != -1)
			{
				exit_status = fork_process(oneCommand[j], args, env, argv[0], cnt);
				return (exit_status); }
		}
		free(oneCommand); }
	return (0);
}
