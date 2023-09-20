#include "shell.h"

/**
 * exitShell - Exits the shell with a specified exit status.
 * @data: Pointer to structure containing optional arguments.
 *
 * Return: 0 if no arguments provided, -2 if custom exit status if specified,
 * or 1 on error.
 */

int exitShell(data_t *data)
{
	int exitStatus;

	if (data->argv[1])
	{
		exitStatus = errStrToInt(data->argv[1]);
		if (exitStatus == -1)
		{
			data->execStat = 2;
			printShellErr(data, "Invalid number: ");
			printErrStr(data->argv[1]);
			printErrChar('\n');
			return (1);
		}
		data->errorCode = errStrToInt(data->argv[1]);
		return (-2);
	}
	data->errorCode = -1;
	return (-2);
}

/**
 * changeDir - Changes the current directory of the process.
 * @data: Pointer to structure containing optional arguments.
 *
 * This function is responsible for changing the current directory of the
 * executing process. The directory to change to can be specified within the
 * data structure.
 *
 * Return: 0 (Always).
 */

int changeDir(data_t *data)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		putStr("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		newDir = getEnvironVar(data, "HOME=");
		if (!newDir)
			chdirResult =
				chdir((newDir = getEnvironVar(data, "PWD=")) ? newDir : "/");
		else
			chdirResult = chdir(newDir);
	}
	else if (cmpStr(data->argv[1], "-") == 0)
	{
		if (!getEnvironVar(data, "OLDPWD="))
		{
			putStr(currentDir);
			putChar('\n');
			return (1);
		}
		putStr(getEnvironVar(data, "OLDPWD=")), putChar('\n');
		chdirResult =
			chdir((newDir = getEnvironVar(data, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirResult = chdir(data->argv[1]);
	if (chdirResult == -1)
	{
		printShellErr(data, "Cannot cd to ");
		printErrStr(data->argv[1]), printErrChar('\n');
	}
	else
	{
		initEnvVar(data, "OLDPWD", getEnvironVar(data, "PWD="));
		initEnvVar(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * dispHelp - Displays help information.
 * @data: Pointer to structure containing optional arguments.
 *
 * This function is responsible for displaying help information or instructions
 * for the program.
 *
 * Return: 0 (Always).
 */

int dispHelp(data_t *data)
{
	char **argArray;

	argArray = data->argv;
	putStr("This function has not been implemented yet.\n");
	if (0)
		putStr(*argArray);
	return (0);
}
