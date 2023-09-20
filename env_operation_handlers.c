#include "shell.h"

/**
 * getEnv - Retrieves a copy of the environment variables as a string array.
 * @data: Pointer to the structure containing optional arguments and variables.
 *
 * This function retrieves a copy of the current environment variables and
 * returns them as a string array.
 *
 * Return: Pointer to the string array containing environment variables.
 */

char **getEnv(data_t *data)
{
	if (!data->environ || data->envChanged)
	{
		data->environ = itemListToArr(data->envList);
		data->envChanged = 0;
	}

	return (data->environ);
}

/**
 * initEnvVar - Initializes a new environment variable or modifies
 * an existing one.
 * @data: Structure containing optional arguments.
 * @varName: The environment variable name.
 * @value: The value to set for the environment variable.
 *
 * This function initializes a new environment variable with @varName and
 * @value or modifies an existing one with the specified variable name.
 *
 * Return: 0 (Always).
 */

int initEnvVar(data_t *data, char *varName, char *value)
{
	char *envVarStr = NULL;
	item_t *currEnvVar;
	char *subStr;

	if (!varName || !value)
		return (0);

	envVarStr = malloc(strLength(varName) + strLength(value) + 2);
	if (!envVarStr)
		return (1);
	copyStr(envVarStr, varName);
	concatStr(envVarStr, "=");
	concatStr(envVarStr, value);
	currEnvVar = data->envList;
	while (currEnvVar)
	{
		subStr = findPrefix(currEnvVar->string, varName);
		if (subStr && *subStr == '=')
		{
			free(currEnvVar->string);
			currEnvVar->string = envVarStr;
			data->envChanged = 1;
			return (0);
		}
		currEnvVar = currEnvVar->next;
	}
	appendNodeToList(&(data->envList), envVarStr, 0);
	free(envVarStr);
	data->envChanged = 1;
	return (0);
}

/**
 * rmvEnvVar - Deletes an environment variable.
 * @data: Pointer to the structure containing optional arguments and variables.
 * @varName: The name of the environment variable to remove.
 *
 * This function removes an environment variable with the specified @varName.
 *
 * Return: 1 if variable is deleted successfully, or 0 otherwise.
 */

int rmvEnvVar(data_t *data, char *varName)
{
	item_t *node = data->envList;
	size_t i = 0;
	char *subStr;

	if (!node || !varName)
		return (0);

	while (node)
	{
		subStr = findPrefix(node->string, varName);
		if (subStr && *subStr == '=')
		{
			data->envChanged = removeNodeAtIdx(&(data->envList), i);
			i = 0;
			node = data->envList;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->envChanged);
}
