#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;

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
char *get_location(char *command);
int _fgetc(FILE *stream);
char *_memcpy(char *dest, char *src, unsigned int n);
char *_strcpy(char *dest, char *src);
void tok(char *s, char *args[]);
int myexitenvcd(char *s, char *args[], char *env[], char *argv0, int cnt);
int fork_process(char *s, char *args[], char *env[], char *argv0, int cnt);
char *inttostring(int num);
int filefd(char *argv[], int fd, char *env[], int cnt);
void removeComment(char *input);
void removeNewline(char *str);
char **splitCommands(char *command, const char *delim);
char *_cd(char **newdir, char *argv0, int cnt);
int space(char *s, int whitespace, int i);
int myexit(char **args, char *argv0, int cnt);
int myenv(char **args, char **env, int e);
char *_getenv(char *name);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);
int check_substring(char *str, char *substring);
int initializer(char **commands, char *argv[], char *env[], int cnt);

#endif
