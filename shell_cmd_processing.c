#include "shell.h"

/**
 * expandCmdAlias - Replaces a command alias with its expanded value.
 * @data: Pointer to the data_t struct containing shell information.
 *
 * This function replaces the current command in @data->argv[0] with its
 * expanded alias value from the @data->aliasList, if command name is found.
 *
 * Return: 1 on success, or 0 otherwise.
 */

int expandCmdAlias(data_t *data)
{
	int idx;
	item_t *aliasNode;
	char *aliasValue;

	for (idx = 0; idx < 10; idx++)
	{
		aliasNode = findNodeWithPrefix(data->aliasList, data->argv[0], '=');
		if (!aliasNode)
			return (0);

		free(data->argv[0]);
		aliasValue = findChar(aliasNode->string, '=');

		if (!aliasValue)
			return (0);

		aliasValue = dupStr(aliasValue + 1);

		if (!aliasValue)
			return (0);

		data->argv[0] = aliasValue;
	}

	return (1);
}

/**
 * isCommandChained - Checks if the current character in the buffer is a
 * command chaining delimiter.
 * @data: Pointer to the data_t struct containing shell information.
 * @buffer: The buffer containing the input.
 * @position: Pointer to the current position in the buffer.
 *
 * This function tests whether the character at the current @position in the
 * buffer is a command chaining delimiter.
 *
 * Return: 1 if it is a command chaining delimiter, or 0 otherwise.
 */

int isCommandChained(data_t *data, char *buffer, size_t *position)
{
	size_t index = *position;

	if (buffer[index] == '|' && buffer[index + 1] == '|')
	{
		buffer[index] = 0;
		index++;
		data->cmdBufType = OR_COMMAND;
	}
	else if (buffer[index] == '&' && buffer[index + 1] == '&')
	{
		buffer[index] = 0;
		index++;
		data->cmdBufType = AND_COMMAND;
	}
	else if (buffer[index] == ';')
	{
		buffer[index] = 0;
		data->cmdBufType = CHAIN_COMMAND;
	}
	else
		return (0);

	*position = index;
	return (1);
}

/**
 * handleCommandChaining - Handles command chaining based on previous
 * command's result.
 * @data: Pointer to the data_t struct containing shell information.
 * @buffer: The character buffer containing the input.
 * @position: Address of the current position in the buffer.
 * @currentIndex: The current index in the buffer.
 * @bufferLength: The length of the buffer.
 *
 * This function checks the type of command chaining (AND or OR) specified by
 * @data->cmdBufType and evaluates the result of the previous command
 * execution.
 *
 * Return: Nothing.
 */

void handleCommandChaining(data_t *data, char *buffer, size_t *position,
				size_t currentIndex, size_t bufferLength)
{
	size_t index = *position;

	if (data->cmdBufType == AND_COMMAND)
	{
		if (data->execStat)
		{
			buffer[currentIndex] = 0;
			index = bufferLength;
		}
	}
	if (data->cmdBufType == OR_COMMAND)
	{
		if (!data->execStat)
		{
			buffer[currentIndex] = 0;
			index = bufferLength;
		}
	}

	*position = index;
}

/**
 * expandVariables - Replaces variables in the command arguments with their
 * values.
 * @data: Pointer to the data_t struct containing shell information.
 *
 * This function iterates through the command arguments in @data->argv and
 * searches for variable references in the arguments, and replaces them with
 * their corresponding values from the environment.
 *
 * Return: 0 on success.
 */

int expandVariables(data_t *data)
{
	int idx = 0;
	item_t *envNode;

	for (idx = 0; data->argv[idx]; idx++)
	{
		if (data->argv[idx][0] != '$' || !data->argv[idx][1])
			continue;

		if (!cmpStr(data->argv[idx], "$?"))
		{
			updateStrPtr(&(data->argv[idx]),
					dupStr(convertNum(data->execStat, 10, 0)));
			continue;
		}
		if (!cmpStr(data->argv[idx], "$$"))
		{
			updateStrPtr(&(data->argv[idx]),
			dupStr(convertNum(getpid(), 10, 0)));
			continue;
		}
		envNode = findNodeWithPrefix(data->envList,
				&data->argv[idx][1], '=');
		if (envNode)
		{
			updateStrPtr(&(data->argv[idx]),
					dupStr(findChar(envNode->string, '=') + 1));
			continue;
		}
		updateStrPtr(&data->argv[idx], dupStr(""));
	}
	return (0);
}

/**
 * updateStrPtr - Replaces an old string with a new one and updates the
 * pointer.
 * @oldStr: Pointer to the old string to be replaced.
 * @newStr: The new string to replace the old one.
 *
 * This function frees the memory occupied by the old string and updates
 * the pointer to point to the new string.
 *
 * Return: 1 on success, 0 on failure.
 */

int updateStrPtr(char **oldStr, char *newStr)
{
	free(*oldStr);
	*oldStr = newStr;
	return (1);
}
