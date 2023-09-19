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
		if (s[i] == '#' && s[i - 1] == ' ')
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
 * splitCommands - split the string by ;
 * @command: the string to be splited
 * Return: the commmads
*/
char **splitCommands(char *command)
{
	int num_commands = 0;
	char **commands = malloc(sizeof(char *) * 10);
	char *token = _strtok(command, ";");

	while (token != NULL)
	{
		commands[num_commands++] = token;
		token = _strtok(NULL, ";");
	}
	commands[num_commands] = NULL;

	return (commands);
}
