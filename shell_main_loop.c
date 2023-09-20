#include "shell.h"

/**
 * runShell - Run the main loop of this shell program.
 * @data: Pointer to the data_t struct containing shell information.
 * @argv: The argument vector from the main function.
 *
 * This function represents the main loop of this custom shell program.
 * It continuously processes user input, executes commands, and manages
 * operations.
 *
 * Return: 0 if successful, or 1 otherwise.
 */

int runShell(data_t *data, char **argv)
{
	ssize_t inputReadRet = 0;
	int builtinCmdRet = 0;

	while (inputReadRet != -1 && builtinCmdRet != -2)
	{
		clearShellData(data);
		if (handleInteractive(data))
			putStr("$ ");
		printErrChar(FLUSH_BUFFER_FLAG);
		inputReadRet = getInput(data);
		if (inputReadRet != -1)
		{
			initShellData(data, argv);
			builtinCmdRet = searchAndExecBuiltin(data);
			if (builtinCmdRet == -1)
				locateAndExecCmd(data);
		}
		else if (handleInteractive(data))
			putChar('\n');
		freeShellData(data, 0);
	}
	savehistoryToFile(data);
	freeShellData(data, 1);
	if (!handleInteractive(data) && data->execStat)
		exit(data->execStat);
	if (builtinCmdRet == -2)
	{
		if (data->errorCode == -1)
			exit(data->execStat);
		exit(data->errorCode);
	}
	return (builtinCmdRet);
}

/**
 * searchAndExecBuiltin - Searches for and processes a built-in command.
 * @data: Pointer to the data_t struct containing shell information.
 *
 * This function searches for a built-in command within the input arguments and
 * executes it if found.
 *
 * Return: 0 if executed successfully,
 *	1 if command is found but not executed successfully,
 *	2 if a command signals an exit() call,
 *	1 if no command is found.
 */

int searchAndExecBuiltin(data_t *data)
{
	int i, builtinResult = -1;
	BuiltinCommand builtinTable[] = {
		{"exit", exitShell},
		{"env", displayEnv},
		{"help", dispHelp},
		{"history", dispHistory},
		{"setenv", initEnvironVar},
		{"unsetenv", rmvEnvironVar},
		{"cd", changeDir},
		{"alias", manageAlias},
		{NULL, NULL}
	};

	for (i = 0; builtinTable[i].command; i++)
		if (cmpStr(data->argv[0], builtinTable[i].command) == 0)
		{
			data->lineCounter++;
			builtinResult = builtinTable[i].function(data);
			break;
		}
	return (builtinResult);
}

/**
 * locateAndExecCmd - Searches for and executes an executable command in
 * PATH directories.
 * @data: Pointer to the data_t struct containing shell information.
 *
 * This function locates and executes an executable command by searching in the
 * directories listed in the 'PATH' environment variable.
 *
 * Return: Nothing.
 */

void locateAndExecCmd(data_t *data)
{
	char *p = NULL;
	int argIdx, num;

	data->commandPath = data->argv[0];
	if (data->lineCounterFlag == 1)
	{
		data->lineCounter++;
		data->lineCounterFlag = 0;
	}
	for (argIdx = 0, num = 0; data->arg[argIdx]; argIdx++)
		if (!isDelim(data->arg[argIdx], " \t\n"))
			num++;
	if (!num)
		return;

	p = findCmdinPath(data, getEnvironVar(data, "PATH="), data->argv[0]);
	if (p)
	{
		data->commandPath = p;
		createChildProcessAndExec(data);
	}
	else
	{
		if ((handleInteractive(data) || getEnvironVar(data, "PATH=")
		|| data->argv[0][0] == '/') && isBuiltinCommand(data, data->argv[0]))
			createChildProcessAndExec(data);
		else if (*(data->arg) != '\n')
		{
			data->execStat = 127;
			printShellErr(data, "command not found\n");
		}
	}
}

/**
 * createChildProcessAndExec - Creates a child process to execute a command.
 * @data: Pointer to the data_t struct containing shell information.
 *
 * This function creates a child process using 'fork()' and executes a command.
 *
 * Return: Nothing.
 */

void createChildProcessAndExec(data_t *data)
{
	pid_t childProcessId;

	childProcessId = fork();
	if (childProcessId == -1)
	{
		perror("Error:");
		return;
	}
	if (childProcessId == 0)
	{
		if (execve(data->commandPath, data->argv, getEnv(data)) == -1)
		{
			freeShellData(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->execStat));
		if (WIFEXITED(data->execStat))
		{
			data->execStat = WEXITSTATUS(data->execStat);
			if (data->execStat == 126)
				printShellErr(data, "access denied\n");
		}
	}
}
