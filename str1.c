#include "shell.h"

/**
 * _strcat - act like strcat function(concatinate string)
 * @dest: destination to add to it
 * @src: addition string(second string to concat to the first)
 * Return: pointer to the total string
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
 * _strcmp - act like strcmp function(compare two strings)
 * @s1: first string
 * @s2: second string
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
 * _strncmp - act like strncmp function(compare n of two strings)
 * @s1: first string
 * @s2: second string
 * @n: number of char to compare
 * Return: int
*/
int _strncmp(char *s1, char *s2, unsigned int n)
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
 * _strspn - act like strspn function
 * @s1: pointer to string1
 * @s2: pointer to string2
 * Return: size_t count
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
 * _strcspn - act like _strcspn function
 * @s1r: pointer to string1
 * @s2r: pointer to string2
 * Return: size_t (s1 - s1r)
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
