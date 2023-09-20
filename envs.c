#include "shell.h"

/**
 * myenv - f
 * @args: char
 * @env: env
 * @e: int
 * Return: int
*/
int myenv(char **args, char **env, int e)
{
	if (args[1] == NULL)
	{
		for (e = 0; env[e] != NULL; e++)
		{
			_puts(env[e]);
			_putchar('\n'); }
		return (0);
	}
	return (1);
}

/**
 * _getenv - f
 * @name: char
 * Return: char
*/
char *_getenv(char *name)
{
	char *equalSign;
	size_t nameLength;
	char **env;

	for (env = environ; *env != NULL; env++)
	{
		equalSign = _strchr(*env, '=');
		if (equalSign == NULL)
			continue;
		nameLength = equalSign - *env;
		if ((_strncmp(*env, name, nameLength) == 0) && (name[nameLength] == '\0'))
			return (equalSign + 1);
	}
	return (NULL);
}

/**
 * _setenv - f
 * @name: char
 * @value: char
 * @overwrite: int
 * Return: int
*/
int _setenv(char *name, char *value, int overwrite)
{
	size_t name_len, value_len, total_len;
	char *new_var;
	char **env, **new_env;

	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);
	if (!overwrite && _getenv(name) != NULL)
		return (0);
	name_len = _strlen(name);
	value_len = _strlen(value);
	total_len = (name_len + value_len + 2);
	new_var = (char *)malloc(total_len);
	if (new_var == NULL)
		return (-1);
	_strcpy(new_var, name);
	new_var[name_len] = '=';
	_strcpy(new_var + name_len + 1, value);
	env = environ;
	while (*env)
	{
		if (_strncmp(*env, name, _strlen(name)) == 0)
			return (0);
		env++; }
	new_env = (char **)_realloc(environ, sizeof(environ),
	((env - environ + 2) * sizeof(char *)));
	if (new_env == NULL)
		return (-1);
	environ = new_env;
	environ[env - environ] = new_var;
	environ[env - environ + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - f
 * @name: char
 * Return: int
*/
int _unsetenv(char *name)
{
	char **env, **next;

	if ((name == NULL) || (name[0] == '\0') || (_strchr(name, '=') != NULL))
		return (-1);
	env = environ;
	next = env;
	while (*env)
	{
		if ((_strncmp(*env, name, _strlen(name)) == 0) &&
		((*env)[_strlen(name)] == '='))
			*env = NULL;
		else
		{
			*next = *env;
			next++;
		}
		env++;
	}
	*next = NULL;
	return (0);
}

/**
 * _myexit - f
 * @args: char
 * @argv0: char
 * @cnt: int
 * Return: int
*/
int _myexit(char **args, char *argv0, int cnt)
{
	int ato = 0;

	if (args[1] != NULL)
	{
		ato = _atoi(args[1]);
		if ((*args[1] < '0') || (*args[1] > '9'))
		{
			write(STDERR_FILENO, argv0, _strlen(argv0));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, inttostring(cnt), (sizeof(cnt) / 4));
			write(STDERR_FILENO, ": exit: Illegal number: ", 24);
			write(STDERR_FILENO, args[1], _strlen(args[1]));
			write(STDERR_FILENO, "\n", 1);
			return (2); }
		else if ((*args[1] > '0') || (*args[1] < '9'))
			return (ato);
	}
	return (0);
}
