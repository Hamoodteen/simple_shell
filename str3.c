#include "shell.h"


int check_substring(const char *str, const char *substring)
{
  for (int i = 0; i < _strlen(str) - _strlen(substring) + 1; i++)
  {
    if (_strncmp(str + i, substring, _strlen(substring)) == 0)
	{
      return (1);
    }
  }
  return (0);
}
