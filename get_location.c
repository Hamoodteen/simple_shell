#include "shell.h"

/**
 * _which - checks if a command exists in the PATH variable
 *
 * @command: the command to be checked
 *
 * Return: on success returns the command path on failure returns NULL
*/
char *_which(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;
	struct stat buffer;

	path = _getenv("PATH");
	if (path)
	{
		if (stat(command, &buffer) == 0)
			return (command);
		path_copy = _strdup(path);
		command_length = _strlen(command);
		path_token = _strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = _strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, command);
			_strcat(file_path, "\0");
			if (stat(file_path, &buffer) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = _strtok(NULL, ":"); }
		}
		free(path_copy);
		return (NULL); }
	return (NULL); }

/**
 * tok - tokanization for the args and convert s to s[0] only like
 * s = "/bin/ls -la" to s = "/bin/ls"
 * @s: the user input like "/bin/ls -la"
 * @args: return like {'/bin/ls', '-la'}
*/
void tok(char *s, char *args[])
{
	int a, i = 0;
	char *tok;

	for (a = 0; a < 50; a++)
		args[a] = NULL;
	tok = _strtok(s, " ");
	while (tok != NULL)
	{
		args[i] = tok;
		tok = _strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
}

/**
 * *_memcpy - f
 * @dest: dest
 * @src: mem
 * @n: num
 * Return: pointer
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];
	return (dest);
}

/**
 * *_strcpy - f
 * @dest: char
 * @src: char
 * Return: Pointer
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * inttostring - f
 * @num: int
 * Return: int
*/
char *inttostring(int num)
{
	int isNegative = 0, temp, strLength, i, digitCount;
	char *str;

	if (num < 0)
	{
		isNegative = 1;
		num = -num; }
	temp = num;
	digitCount = 1;
	while (temp >= 10)
	{
		temp /= 10;
		digitCount++; }
	strLength = digitCount + isNegative + 1;
	str = (char *)malloc(strLength);
	if (str == NULL)
		return (NULL);
	str[strLength - 1] = '\0';
	for (i = strLength - 2; i >= isNegative; i--)
	{
		str[i] = '0' + (num % 10);
		num /= 10; }
	if (isNegative)
		str[0] = '-';
	return (str);
}
