#include "shell.h"

/**
 * initEnvironVar - Modifies or creates an environment variable.
 * @data: Pointer to a structure containing optional arguments and variables.
 *
 * This function is responsible for checking arguments and delegating on
 * modifying an existing environment variable or creating a new one if it
 * does not exist.
 *
 * Return: 0 if successful, or 1 otherwise.
 */

int initEnvironVar(data_t *data)
{
	if (data->argc != 3)
	{
		printErrStr("Number of arguments provided is not correct\n");
		return (1);
	}
	if (initEnvVar(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * rmvEnvironVar - Deletes an environment variable.
 * @data: Pointer to the structure containing optional arguments.
 *
 * This function is responsible for checking arguments and delegating on
 * deleting an environment variable.
 *
 * Return: 0 if successful, or 1 otherwise.
 */

int rmvEnvironVar(data_t *data)
{
	int idx;

	if (data->argc == 1)
	{
		printErrStr("Incorrect number of arguments provided.\n");
		return (1);
	}
	for (idx = 1; idx <= data->argc; idx++)
		rmvEnvVar(data, data->argv[idx]);

	return (0);
}

/**
 * displayEnv - Prints the current environment variables.
 * @data: A structure containing optional arguments.
 *
 * This function is responsible for displaying the current environment
 * variables.
 *
 * Return: 0 (Always).
 */

int displayEnv(data_t *data)
{
	displayStrList(data->envList);
	return (0);
}

/**
 * initEnvList - Initializes the environment linked list.
 * @data: Pointer to a structure containing optional arguments and environment
 * variables
 *
 * This function is responsible for initializing and populating the linked list
 * of environment variables.
 *
 * Return: 0 (Always).
 */

int initEnvList(data_t *data)
{
	size_t idx;
	item_t *node = NULL;

	for (idx = 0; environ[idx]; idx++)
		appendNodeToList(&node, environ[idx], 0);
	data->envList = node;
	return (0);
}

/**
 * getEnvironVar - Retrieves the value of an environment variable by name.
 * @data: Pointer to a structure containing optional arguments and environment
 * variables.
 * @name: The name of the environment variable to retrieve.
 *
 * This function is responsible for fetching the value of the specified
 * environment variable based on its name.
 *
 * Return: The value of the environment variable or NULL if not found.
 */

char *getEnvironVar(data_t *data, const char *name)
{
	item_t *node = data->envList;
	char *value;

	while (node)
	{
		value = findPrefix(node->string, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}
