#include "shell.h"

/**
 * displayStrList - Prints only the string element of a item_t linked list.
 * @head: Pointer to the head node of the linked list.
 *
 * This function displays the string elements of the linked list pointed to
 * by @head.
 *
 * Return: The number of elements in the list.
 */

size_t displayStrList(const item_t *head)
{
	size_t size = 0;

	while (head)
	{
		putStr(head->string ? head->string : "(nil)");
		putStr("\n");
		head = head->next;
		size++;
	}
	return (size);
}

/**
 * removeNodeAtIdx - Deletes a node at the specified index in a linked list.
 * @head: Pointer to the pointer of the head node.
 * @index: The index of the node to delete.
 *
 * This function deletes the node at the specified 'index' in the linked list
 * pointed to by @head.
 *
 * Return: 1 on success, 0 on failure
 */

int removeNodeAtIdx(item_t **head, unsigned int index)
{
	item_t *currentNode, *prevNode;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		currentNode = *head;
		*head = (*head)->next;
		free(currentNode->string);
		free(currentNode);
		return (1);
	}

	currentNode = *head;
	while (currentNode)
	{
		if (i == index)
		{
			prevNode->next = currentNode->next;
			free(currentNode->string);
			free(currentNode);
			return (1);
		}
		i++;
		prevNode = currentNode;
		currentNode = currentNode->next;
	}
	return (0);
}

/**
 * prependNodeToList - Adds a new node to the beginning of a linked list.
 * @head: Pointer to the pointer of the head node.
 * @data: String data for the new node.
 * @index: Index used for history reference.
 *
 * This function creates a new node with the provided data and adds it to the
 * beginning of the linked list specified by 'head'.
 *
 * Return: Address of the new node, or NULL on failure.
 */

item_t *prependNodeToList(item_t **head, const char *data, int index)
{
	item_t *newNode;

	if (!head)
		return (NULL);

	newNode = malloc(sizeof(item_t));
	if (!newNode)
		return (NULL);

	fillMemWithByte((void *)newNode, 0, sizeof(item_t));
	newNode->number = index;

	if (data)
	{
		newNode->string = dupStr(data);
		if (!newNode->string)
		{
			free(newNode);
			return (NULL);
		}
	}
	else
	{
		newNode->string = NULL;
	}

	newNode->next = *head;
	*head = newNode;

	return (newNode);
}

/**
 * freeLinkedList - Frees all nodes of an item_t linked list.
 * @head: Pointer to the pointer of the head node.
 *
 * This function deallocates the memory of all nodes in the linked list
 * pointed to by @head.
 *
 * Return: Nothing.
 */

void freeLinkedList(item_t **head)
{
	item_t *currentNode, *nextNode, *temp;

	if (!head || !*head)
		return;

	temp = *head;
	currentNode = temp;
	while (currentNode)
	{
		nextNode = currentNode->next;
		free(currentNode->string);
		free(currentNode);
		currentNode = nextNode;
	}
	*head = NULL;
}

/**
 * appendNodeToList - Adds a new node to the end of the linked list.
 * @head: Pointer to the pointer of the head node.
 * @data: String data for the new node.
 * @index: Index used for history reference.
 *
 * This function creates a new node with the provided data and appends it to
 * the end of the linked list specified by @head.
 *
 * Return: Address of the new node, or NULL on failure.
 */

item_t *appendNodeToList(item_t **head, const char *data, int index)
{
	item_t *newNode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNode = malloc(sizeof(item_t));
	if (!newNode)
		return (NULL);
	fillMemWithByte((void *)newNode, 0, sizeof(item_t));
	newNode->number = index;
	if (data)
	{
		newNode->string = dupStr(data);
		if (!newNode->string)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;
	return (newNode);
}
