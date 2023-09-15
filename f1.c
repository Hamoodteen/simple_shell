#include "shell.h"

/**
 * _putchar - prints a string
 * @c: pointer to string to print
 * Return: string
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string
 * @c: pointer to string to print
 * Return: string
 */
int _puts(char *c)
{
	return (write(1, &c[0], _strlen(c)));
}

/**
 * print_number - f
 * @n: int
 * Return: int
*/
int print_number(long int n)
{
	long int divisor;
	long int tmp;
	int cnt = 0;

	if (n < 0)
	{
		_putchar('-');
		n = -n;
		cnt++;
	}
	divisor = 1;
	tmp = n;
	while (tmp / 10 > 0)
	{
		divisor *= 10;
		tmp /= 10;
	}
	while (divisor > 0)
	{
		cnt++;
		_putchar('0' + n / divisor);
		n %= divisor;
		divisor /= 10;
	}
	return (cnt);
}

/**
 * _getline - f
 * @lineptr: char
 * @n: int
 * @stream: file
 * Return: int
*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	char *newline, *line = NULL;
	ssize_t bufsize = 128, nchars = 0;
	int c;

	if ((lineptr == NULL) || (n == NULL) || (stream == NULL))
		return (-1);
	if ((*lineptr == NULL) || (*n == 0))
	{
		line = (char *)malloc(bufsize);
		if (line == NULL)
			return (-1);
		*n = bufsize; }
	else
	{
		bufsize = *n;
		line = *lineptr; }
	while (1)
	{
		c = fgetc(stream);
		if ((c == EOF) || (c == '\n'))
		{
			line[nchars] = '\0';
			break; }
		if (nchars >= (bufsize - 1))
		{
			bufsize *= 2;
			newline = (char *)_realloc(line, 0, bufsize);
			if (newline == NULL)
			{
				free(line);
				return (-1); }
			line = newline;
		}
		line[nchars++] = (char)c; }
	*lineptr = line;
	*n = bufsize;
	if ((nchars == 0) && (c == EOF))
		return (-1);
	return (nchars);
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
