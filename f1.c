#include "shell.h"

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
		_puts("-");
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
		_puts("0" + (n / divisor));
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
	static char buffer[BUFFER_SIZE];
	static size_t buffer_pos, buffer_size;
	size_t line_length, bytes_read, i, wg;
	char *line_end = NULL;
		buffer_pos = buffer_size = line_length = i = 0;
		if (lineptr == NULL || n == NULL || stream == NULL)
			return (-1);
		if (buffer_pos >= buffer_size)
		{
			bytes_read = read(fileno(stream), buffer, BUFFER_SIZE);
			if (bytes_read <= 0)
				return (-1);
			buffer_size = (size_t)bytes_read;
			buffer_pos = 0; }
		while (buffer_pos + line_length < buffer_size)
		{
			if (buffer[buffer_pos + line_length] == '\n')
			{
				line_end = &buffer[buffer_pos + line_length];
				break; }
			line_length++; }
		if (line_end != NULL)
		{
			line_length++;
			if (*lineptr == NULL || *n < line_length)
			{
				*lineptr = (char *)realloc(*lineptr, line_length);
				if (*lineptr == NULL)
					return (-1);
				*n = line_length; }
			for (i = 0; i < line_length; i++)
				(*lineptr)[i] = buffer[buffer_pos + i];
			buffer_pos += line_length;
			return ((ssize_t)line_length); }
		while (1)
		{
			wg = whileget(lineptr, n, bytes_read, line_length,
			buffer_pos, buffer_size, stream, buffer, line_end, i);
			return (wg); }
}

/**
 * whileget - f
 * @lineptr: lineptr
 * @n: n
 * @bytes_read: bytes_read
 * @line_length: line_length
 * @buffer_pos: buffer_pos
 * @buffer_size: buffer_size
 * @stream: stream
 * @buffer: buffer
 * @line_end: line_end
 * @i: i
 * Return: int
*/
ssize_t whileget(char **lineptr, size_t *n, size_t bytes_read,
size_t line_length, size_t buffer_pos, size_t buffer_size,
FILE *stream, char buffer[], char *line_end, size_t i)
{
	bytes_read = read(fileno(stream), buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (-1);
	buffer_size = (size_t)bytes_read;
	buffer_pos = 0;
	while (buffer_pos + line_length < buffer_size)
	{
		if (buffer[buffer_pos + line_length] == '\n')
		{
			line_end = &buffer[buffer_pos + line_length];
			break; }
		line_length++; }
	if (line_end != NULL)
	{
		line_length++;
		if (*lineptr == NULL || *n < line_length)
		{
			*lineptr = (char *)realloc(*lineptr, line_length);
			if (*lineptr == NULL)
				return (-1);
			*n = line_length; }
		for (i = 0; i < line_length; i++)
			(*lineptr)[i] = buffer[buffer_pos + i];
		buffer_pos += line_length;
		return ((ssize_t)line_length); }
	return (0);
}

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
