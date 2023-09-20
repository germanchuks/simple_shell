#include "shell.h"

/**
 * unsetAlias - Removes an alias from the alias list.
 * @data: Pointer to a structure containing optional arguments.
 * @string: The string alias to be removed.
 *
 * This function is responsible for removing an alias specified by @string
 * from the alias list.
 *
 * Return: 0 if successful, or 1 otherwise.
 */

int unsetAlias(data_t *data, char *string)
{
	char *eqlPosition, savedChar;
	int result;

	eqlPosition = findChar(string, '=');
	if (!eqlPosition)
		return (1);
	savedChar = *eqlPosition;
	*eqlPosition = 0;
	result = removeNodeAtIdx(&(data->aliasList),
			findNodeIndex(data->aliasList,
			findNodeWithPrefix(data->aliasList, string, -1)));
	*eqlPosition = savedChar;
	return (result);
}

/**
 * setAlias - Sets an alias for a string in the alias list.
 * @data: Pointer to the parameter struct.
 * @string: The string containing the alias assignment.
 *
 * This function is responsible for defining and storing an alias
 * for a specified string within the alias list.
 *
 * Return: 0 on success, 1 on error.
 */

int setAlias(data_t *data, char *string)
{
	char *eqlPosition;

	eqlPosition = findChar(string, '=');
	if (!eqlPosition)
		return (1);
	if (!*++eqlPosition)
		return (unsetAlias(data, string));

	unsetAlias(data, string);
	return (appendNodeToList(&(data->aliasList), string, 0) == NULL);
}

/**
 * printAlias - Prints an alias string.
 * @node: Pointer to the alias node containing the string to be printed.
 *
 * Return: 0 if successful, or 1 otherwise.
 */

int printAlias(item_t *node)
{
	char *eqlPosition = NULL, *a = NULL;

	if (node)
	{
		eqlPosition = findChar(node->string, '=');
		for (a = node->string; a <= eqlPosition; a++)
			putChar(*a);
		putChar('\'');
		putStr(eqlPosition + 1);
		putStr("'\n");
		return (0);
	}
	return (1);
}

/**
 * manageAlias - Controls alias commands, emulating the alias built-in.
 * @data: Pointer to a structure containing optional arguments and the alias
 * list.
 *
 * Return: 0 (Always).
 */

int manageAlias(data_t *data)
{
	char *eqlPosition = NULL;
	item_t *node = NULL;
	int i = 0;

	if (data->argc == 1)
	{
		node = data->aliasList;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		eqlPosition = findChar(data->argv[i], '=');
		if (eqlPosition)
			setAlias(data, data->argv[i]);
		else
			printAlias(findNodeWithPrefix(data->aliasList, data->argv[i], '='));
	}

	return (0);
}

/**
 * dispHistory - Displays the command history list with line numbers.
 * @data: A structure containing optional arguments and the history list.
 *
 * This function displays the command history list along with line numbers,
 * to help users identify previous commands.
 *
 * Return: 0 (Always).
 */

int dispHistory(data_t *data)
{
	displayList(data->historyList);
	return (0);
}
