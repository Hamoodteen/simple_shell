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
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int	_strncmp(char *s1, char *s2, unsigned int n);
size_t _strspn(const char *s1, const char *s2);
size_t _strcspn(const char *s1r, const char *s2r);
int _strlen(const char *s);
char *_strchr(const char *s, int c);
char *_strdup(char *str);
char *_strtok(char *str, const char *del);
int _atoi(char *s);
char *_which(char *command);
int _fgetc(FILE *stream);
char *_memcpy(char *dest, char *src, unsigned int n);
char *_strcpy(char *dest, char *src);
void tok(char *s, char *args[]);
int myexitenv(char *s, char *args[]);
void fork_process(char *s, char *args[]);

#endif
