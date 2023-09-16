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
		c = _fgetc(stream);
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
	return (nchars); }

/**
 * *_realloc - f
 * @ptr: pointer
 * @old_size: int
 * @new_size: int
 * Return: pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ptr1;
	char *old_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	ptr1 = malloc(new_size);
	if (!ptr1)
		return (NULL);
	old_ptr = ptr;
	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			ptr1[i] = old_ptr[i];
	}
	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			ptr1[i] = old_ptr[i];
	}
	free(ptr);
	return (ptr1);
}
