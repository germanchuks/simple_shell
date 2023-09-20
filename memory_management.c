#include "shell.h"

/**
 * freePointer - Frees the memory pointed to by a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * This function frees the memory pointed to by a pointer and sets the
 * pointer itself to NULL.
 *
 * Return: 1 if memory was freed successfully, 0 if ptr
 * was NULL or already NULL.
 */

int freePointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
