#include "shell.h"

/**
 * memRealloc - Reallocates a block of memory to a new size.
 * @prevPtr: Pointer to the previous memory block.
 * @prevSize: Byte size of the previous block.
 * @newSize: Byte size of the new block.
 *
 * This function reallocates memory pointed to by @prevPtr to a new size
 * specified by @newSize.
 *
 * Return: Pointer to the reallocated block or NULL it it fails.
 */

void *memRealloc(void *prevPtr, unsigned int prevSize, unsigned int newSize)
{
	char *newPtr;

	if (!prevPtr)
		return (malloc(newSize));
	if (!newSize)
	{
		free(prevPtr);
		return (NULL);
	}
	if (newSize == prevSize)
		return (prevPtr);

	newPtr = malloc(newSize);
	if (!newPtr)
		return (NULL);

	prevSize = prevSize < newSize ? prevSize : newSize;
	while (prevSize--)
		newPtr[prevSize] = ((char *)prevPtr)[prevSize];

	free(prevPtr);
	return (newPtr);
}

/**
 * fillMemWithByte - Fills a block of memory with a specified byte value.
 * @dest: A pointer to the memory block to be filled.
 * @byte: The byte value used for filling the memory block.
 * @size: The number of bytes to fill with the specified byte value.
 *
 * This function fills a memory block pointed to by @dest with the specified
 * @byte value.
 *
 * Return: A pointer to the memory block @dest.
 */

char *fillMemWithByte(char *dest, char byte, unsigned int size)
{
	unsigned int byteIndex;

	for (byteIndex = 0; byteIndex < size; byteIndex++)
	{
		dest[byteIndex] = byte;
	}
	return (dest);
}

/**
 * freeStrArr - Deallocates memory for a string array and its strings.
 * @strArray: Pointer to the string array to deallocate.
 *
 * This function frees the memory of a string array @strArray and the strings
 * it points to.
 *
 * Return: Nothing.
 */

void freeStrArr(char **strArray)
{
	char **temp = strArray;

	if (!strArray)
		return;

	while (*strArray)
	{
		free(*strArray);
		strArray++;
	}

	free(temp);
}
