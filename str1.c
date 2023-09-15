#include "shell.h"

/**
 * _strcat - f
 * @dest: str
 * @src: str
 * Return: pointer
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - f
 * @s1: first
 * @s2: second
 * Return: int
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * _strncmp - f
 * @s1: char
 * @s2: char
 * @n: int
 * Return: int
*/
int	_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i = 0;

	while ((s1[i] != '\0') && (s2[i] != '\0') && (i < n))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	if (i != n)
		return (s1[i] - s2[i]);
	return (0);
}

/**
 * _strspn - f
 * @s1: char
 * @s2: char
 * Return: int
*/
size_t _strspn(const char *s1, const char *s2)
{
	size_t count;

	count = 0;
	while (*s1)
	{
		if (_strchr(s2, *s1))
			count++;
		else
			break;
		s1++;
	}
	return (count);
}

/**
 * _strcspn - f
 * @s1r: char
 * @s2r: char
 * Return: int
*/
size_t _strcspn(const char *s1r, const char *s2r)
{
	const char *s1 = s1r;
	const char *s2;

	while (*s1)
	{
		s2 = s2r;
		while (*s2)
		{
			if (*s1 == *s2++)
				return (s1 - s1r);
		}
		s1++;
	}
	return (s1 - s1r);
}
