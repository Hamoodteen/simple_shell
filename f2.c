#include "shell.h"

/**
 * removeComment - removes everything after a '#' char
 * @s: user input string
 */
void removeComment(char *s)
{
	int i = 0;

	if (s[i] == '#')
		s[i] = '\0';
	while (s[i] != '\0')
	{
		if ((s[i] == '#') && (s[i - 1] == ' '))
			break;
		i++;
	}
	s[i] = '\0';
}

/**
 *removeNewline - removes new line from a string
 *@s: user input string
 */
void removeNewline(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			break;
		i++;
	}
	s[i] = '\0';
}

/**
 * space - f
 * @s: char
 * @whitespace: int
 * @i: int
 * Return: int
*/
int space(char *s, int whitespace, int i)
{
	s[_strcspn(s, "\n")] = '\0';
	whitespace = 1;
	for (i = 0; s[i] != '\0'; i++)
	{
		if ((unsigned char)s[i] != ' ')
		{
			whitespace = 0;
			break; }
	}
	return (whitespace);
}

/**
 * splitCommands - split the string by ;
 * @command: the string to be splited
 * @delim: the seperator like " " or ";"
 * Return: the commmads
*/
char **splitCommands(char *command, const char *delim)
{
	int num_commands = 0;
	char **commands = malloc(sizeof(char *) * 10);
	char *token = _strtok(command, delim);

	while (token != NULL)
	{
		commands[num_commands++] = token;
		token = _strtok(NULL, delim);
	}
	commands[num_commands] = NULL;

	return (commands);
}

/**
 * _cd - f
 * @newdir: char
 * @argv0: argv0
 * @cnt: int
 * Return: char
*/
char *_cd(char **newdir, char *argv0, int cnt)
{
	char *homedir = _getenv("HOME");
	char *oldpath;

	if (newdir[1] == NULL)
	{
		chdir(homedir);
		_setenv("PWD", homedir, 1);
		return (homedir); }
	if (_strcmp(newdir[1], "-") == 0)
	{
		oldpath = _getenv("PWD");
		chdir(oldpath);
		_setenv("PWD", oldpath, 1);
		return (oldpath);
	}
	else
	{
		if (chdir(newdir[1]) == 0)
		{
			_setenv("PWD", newdir[1], 1);
			return (newdir[1]);
		}
		else
		{
			oldpath = _getenv("PWD");
			write(STDERR_FILENO, argv0, _strlen(argv0));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, inttostring(cnt), (sizeof(cnt) / 4));
			write(STDERR_FILENO, ": cd: can't cd to ", 18);
			write(STDERR_FILENO, newdir[1], _strlen(newdir[1]));
			write(STDERR_FILENO, "\n", 1);
			return (oldpath);
		}
	}
}
