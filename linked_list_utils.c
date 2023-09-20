#include "shell.h"

/**
 * displayList - Prints all elements of a item_t linked list.
 * @head: The pointer to the address of the head node.
 *
 * This function prints each element of the linked list.
 *
 * Return: The size of the list.
 */

size_t displayList(const item_t *head)
{
	size_t listSize = 0;

	while (head)
	{
		putStr(convertNum(head->number, 10, 0));
		putChar(':');
		putChar(' ');
		putStr(head->string ? head->string : "(nil)");
		putStr("\n");
		head = head->next;
		listSize++;
	}

	return (listSize);
}

/**
 * findNodeIndex - Finds the index of a specific node in a linked list.
 * @head: The pointer to the address of the head node.
 * @targetNode: The node to search for within the linked list.
 *
 * Return: The index of the node or -1 if not found.
 */

ssize_t findNodeIndex(item_t *head, item_t *targetNode)
{
	size_t nodeIndex = 0;

	while (head)
	{
		if (head == targetNode)
			return (nodeIndex);
		head = head->next;
		nodeIndex++;
	}

	return (-1);
}

/**
 * itemListToArr - Converts a item_t linked list into an array of strings.
 * @head: Pointer to the address of the head node.
 *
 * This function converts the linked list of strings pointed to by @head into
 * an array of strings.
 *
 * Return: An array of strings, or NULL on failure.
 */

char **itemListToArr(item_t *head)
{
	char *string;
	char **stringArr;
	item_t *node = head;
	size_t currentIdx;
	size_t numNodes = getListLen(head);

	if (!head || !numNodes)
		return (NULL);

	stringArr = malloc(sizeof(char *) * (numNodes + 1));
	if (!stringArr)
		return (NULL);

	for (numNodes = 0; node; node = node->next, numNodes++)
	{
		string = malloc(strLength(node->string) + 1);
		if (!string)
		{
			for (currentIdx = 0; currentIdx < numNodes; currentIdx++)
				free(stringArr[currentIdx]);
			free(stringArr);
			return (NULL);
		}

		string = copyStr(string, node->string);
		stringArr[numNodes] = string;
	}

	stringArr[numNodes] = NULL;
	return (stringArr);
}

/**
 * getListLen - Determines the length of a item_t linked list.
 * @head: The pointer to the address of the head node.
 *
 * This function counts and returns the number of nodes in the linked list.
 *
 * Return: The size of the list.
 */

size_t getListLen(const item_t *head)
{
	size_t listSize = 0;

	while (head)
	{
		head = head->next;
		listSize++;
	}
	return (listSize);
}

/**
 * findNodeWithPrefix - Finds a node with a string starting with a prefix and
 * has a specific character following it.
 * @head: The pointer to the address of the head node.
 * @prefix: The prefix to match at the beginning of the string.
 * @nChar: The character to match following the prefix (-1 if not specified).
 *
 * Return: Matching node or NULL.
 */

item_t *findNodeWithPrefix(item_t *head, char *prefix, char nChar)
{
	char *subStrStart = NULL;

	while (head)
	{
		subStrStart = findPrefix(head->string, prefix);
		if (subStrStart && ((nChar == -1) || (*subStrStart == nChar)))
			return (head);
		head = head->next;
	}

	return (NULL);
}
