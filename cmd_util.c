#include "shell.h"

/**
 * copyCharacters - Copies characters from a source string.
 *
 * @source: The source string.
 * @subStrBegin: The beginning index of the substring.
 * @subStrEnd: The ending index of the substring.
 *
 * This function extracts characters from the source string within the
 * specified range, excluding colons.
 *
 * Return: Pointer to the new buffer containing the copied substring.
 */

char *copyCharacters(char *source, int subStrBegin, int subStrEnd)
{
	int srcIndex = 0;
	int bufIndex = 0;
	static char buffer[1024];

	for (srcIndex = subStrBegin; srcIndex < subStrEnd; srcIndex++)
	{
		if (source[srcIndex] != ':')
		{
			buffer[bufIndex] = source[srcIndex];
			bufIndex++;
		}
	}

	buffer[bufIndex] = 0;

	return (buffer);
}

/**
 * findCmdInPath - Finds the full path of a command in the PATH environment.
 * @data: Pointer to the data struct (UNUSED).
 * @pathEnv: The PATH string containing directories separated by colons.
 * @cmdName: The command to find.
 *
 * This function searches for the full path of a command within directories
 * listed in the PATH environment variable.
 *
 * Return: Full path of the command if found, or NULL if not found.
 */

char *findCmdInPath(data_t *data, char *pathEnv, char *cmdName)
{
	int pathIdx = 0;
	int partStrt = 0;
	char *path;

	(void)data;

	if (!pathEnv)
		return (NULL);

	if ((strLength(cmdName) > 2) && findPrefix(cmdName, "./"))
	{
		if (isBuiltinCommand(data, cmdName))
			return (cmdName);
	}

	while (1)
	{
		if (!pathEnv[pathIdx] || pathEnv[pathIdx] == ':')
		{
			path = copyCharacters(pathEnv, partStrt, pathIdx);

			if (!*path)
				concatStr(path, cmdName);
			else
			{
				concatStr(path, "/");
				concatStr(path, cmdName);
			}

			if (isBuiltinCommand(data, path))
				return (path);

			if (!pathEnv[pathIdx])
				break;
			partStrt = pathIdx;
		}
		pathIdx++;
	}

	return (NULL);
}

/**
 * isBuiltinCommand - Checks if a given command is a built-in command.
 * @data: Pointer to the data struct (UNUSED).
 * @command: The command to check.
 *
 * This function checks whether a given command is an external executable file
 * by examining its file status using the stat function.
 *
 * Return: 1 if the command is a built-in, 0 otherwise.
 */

int isBuiltinCommand(data_t *data, char *command)
{
	struct stat fileStat;

	(void)data;

	if (!command || stat(command, &fileStat))
		return (0);

	if (fileStat.st_mode & S_IFREG)
		return (1);

	return (0);
}
