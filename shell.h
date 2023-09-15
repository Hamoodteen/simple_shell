#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;
int _putchar(char c);
int _puts(char *c);
int print_number(long int n);
int _strlen(const char *s);
int _atoi(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int	_strncmp(char *s1, char *s2, unsigned int n);
size_t _strcspn(const char *s1r, const char *s2r);
char *_memcpy(char *dest, char *src, unsigned int n);
char *_which(char *command);

#endif
