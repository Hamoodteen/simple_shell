#include "shell.h"

/**
 * _strlen - do something
 * @s: int or char
 * Return: some thing
 */
int _strlen(const char *s)
{
	int len = 0;
	int i;

	for (i = 0; s[i] != '\0'; i++)
		len++;
	return (len);
}

/**
 * _strchr - f
 * @s: char
 * @c: int
 * Return: char
*/
char *_strchr(const char *s, int c)
{
	char *result = NULL;

	while (*s != '\0')
	{
		if (*s == c)
		{
			result = (char *)s;
			break;
		}
		s++;
	}
	return (result);
}

/**
 * _strdup - f
 * @str: string
 * Return: pointer
 */
char *_strdup(char *str)
{
	char *copy;
	int i, len = 0;

	if (str == NULL)
		return (NULL);
	while (str[len] != '\0')
		len++;
	copy = (char *)malloc((sizeof(char) * len) + 1);
	if (copy == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		copy[i] = str[i];
	copy[len] = '\0';
	return (copy);
}

/**
 * _strtok - f
 * @str: str
 * @del: str
 * Return: char
*/
char *_strtok(char *str, const char *del)
{
	static char *nextToken;
	char *tokenStart;

	if (str != NULL)
		nextToken = str;
	while (*nextToken != '\0' && _strchr(del, *nextToken) != NULL)
		nextToken++;
	if (*nextToken == '\0')
		return (NULL);
	tokenStart = nextToken;
	while (*nextToken != '\0' && _strchr(del, *nextToken) == NULL)
		nextToken++;
	if (*nextToken != '\0')
	{
		*nextToken = '\0';
		nextToken++;
	}
	return (tokenStart);
}

/**
 * _atoi - f
 * @s: str
 * Return: int
 */
int _atoi(char *s)
{
	int i, d, n, len, f, digit;

	i = 0;
	d = 0;
	n = 0;
	len = 0;
	f = 0;
	digit = 0;

	while (s[len] != '\0')
		len++;
	while ((i < len) && (f == 0))
	{
		if (s[i] == '-')
			++d;
		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}
	if (f == 0)
		return (0);
	return (n);
}
