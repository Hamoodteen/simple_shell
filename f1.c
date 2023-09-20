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
	char *newline, *line = NULL;
	ssize_t bufsize = 8192, nchars = 0;
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
			newline = (char *)_realloc(line, sizeof(line), bufsize);
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
	int i, j, ex_st = 0;

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
			ex_st = myexitenvcd(oneCommand[j], args, env, argv[0], cnt);
			if (ex_st == 2)
				break;
			if (ex_st != 0)
				ex_st = fork_process(oneCommand[j], args, env, argv[0], cnt);
		}
		free(oneCommand);
	}
	return (ex_st);
}
