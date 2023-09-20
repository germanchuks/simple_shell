#include "shell.h"

/**
 * main - Entry point
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * This is the main function of the shell program. It initializes data
 * structures, processes command-line arguments, and executes the shell logic.
 *
 * Return: 0 if successful, or 1 otherwise.
 */

int main(int argc, char **argv)
{
	int fileDesc = 2;
	data_t data[] = { INIT_SHELL_INFO };

	asm ("mov %1, %0\n\t"
		 "add $3, %0"
		 : "=r" (fileDesc)
		 : "r" (fileDesc));

	if (argc == 2)
	{
		fileDesc = open(argv[1], O_RDONLY);
		if (fileDesc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				printErrStr(argv[0]);
				printErrStr(": 0: Cannot access ");
				printErrStr(argv[1]);
				printErrChar('\n');
				printErrChar(FLUSH_BUFFER_FLAG);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readDescriptor = fileDesc;
	}

	initEnvList(data);
	loadHistoryFromFile(data);
	runShell(data, argv);

	return (EXIT_SUCCESS);
}
