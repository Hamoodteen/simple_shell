#include "shell.h"

/**
 * execution - execute the actual command with execve
 * @argv: like: {'ls', '-la'} which argv[0] is the command
*/
void execution(char **argv)
{
	if (argv)
	{
		/* get the command */

		/* generate the path to this command before passing it to execve */
		argv[0] = get_location(argv[0]);

		/* execute the actual command with execve */
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error:");
		}
	}

}
