#include "shell.h"

/**
 * initShellData - Initializes the data_t struct with command-line arguments.
 * @data: Pointer to the structure to be initialized.
 * @argVect: Argument vector containing command-line arguments.
 *
 * This function initializes the 'data_t' structure with information
 * from the command-line arguments, including the program name, argument count,
 * and argument vector. It also processes and replaces aliases and variables
 * in the provided arguments.
 *
 * Return: Nothing.
 */

void initShellData(data_t *data, char **argVect)
{
	int argIndex = 0;

	data->fName = argVect[0];
	if (data->arg)
	{
		data->argv = strTokenize(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = dupStr(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (argIndex = 0; data->argv && data->argv[argIndex]; argIndex++)
			;
		data->argc = argIndex;
		expandCmdAlias(data);
		expandVariables(data);
	}
}

/**
 * freeShellData - Frees resources of data_t struct.
 * @data: Pointer to the structure whose resources needs to be freed.
 * @freeAll: True if freeing all resources.
 *
 * This function is responsible for freeing resources associated with the
 * @data_t structure. When @freeAll is set to true, it frees all resources
 * including environment variables, history, aliases, etc.
 *
 * Return: Nothing.
 */

void freeShellData(data_t *data, int freeAll)
{
	freeStrArr(data->argv);
	data->argv = NULL;
	data->commandPath = NULL;

	if (freeAll)
	{
		if (!data->cmdBuf)
			free(data->arg);
		if (data->envList)
			freeLinkedList(&(data->envList));
		if (data->historyList)
			freeLinkedList(&(data->historyList));
		if (data->aliasList)
			freeLinkedList(&(data->aliasList));
		freeStrArr(data->environ);
		data->environ = NULL;
		freePointer((void **)data->cmdBuf);
		if (data->readDescriptor > 2)
			close(data->readDescriptor);
		putChar(FLUSH_BUFFER_FLAG);
	}
}

/**
 * clearShellData - Resets the data_t structure for shell-related information.
 * @data: Pointer to the structure to be reset.
 *
 * This function resets the @data_t structure, clearing any existing data
 * related to shell information. It sets various members of the structure to
 * NULL or zero, ensuring a clean slate for further shell operations.
 *
 * Return: Nothing.
 */

void clearShellData(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->commandPath = NULL;
	data->argc = 0;
}
