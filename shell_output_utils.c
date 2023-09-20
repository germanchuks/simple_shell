#include "shell.h"

/**
 * putStr - Prints a string to the standard output.
 * @string: The string to be printed.
 *
 * Return: Nothing.
 */

void putStr(char *string)
{
	int index = 0;

	if (!string)
		return;

	while (string[index] != '\0')
	{
		putChar(string[index]);
		index++;
	}
}

/**
 * putChar - Writes a character to the standard output.
 * @character: The character to print.
 *
 * Return: 1 on success, -1 if error occurs with errno set accordingly.
 */

int putChar(char character)
{
	static char buffer[WRITE_BUFFER_SIZE];
	static int index;

	if (character == FLUSH_BUFFER_FLAG || index >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}

	if (character != FLUSH_BUFFER_FLAG)
	{
		buffer[index++] = character;
	}

	return (1);
}

/**
 * copyStr - Copies a string from srcBuffer to destBuffer.
 *
 * @destBuffer: The destination buffer.
 * @srcBuffer: The source buffer to be copied from.
 *
 * Return: A pointer to the destination buffer.
 */

char *copyStr(char *destBuffer, char *srcBuffer)
{
	int index = 0;

	if (destBuffer == srcBuffer || srcBuffer == NULL)
		return (destBuffer);

	while (srcBuffer[index])
	{
		destBuffer[index] = srcBuffer[index];
		index++;
	}

	destBuffer[index] = 0;

	return (destBuffer);
}

/**
 * dupStr - Duplicates a string.
 * @originalStr: The string to be duplicated.
 *
 * Return: A pointer to the duplicated string or NULL on failure.
 */

char *dupStr(const char *originalStr)
{
	int length = 0;
	char *dupStr;

	if (originalStr == NULL)
		return (NULL);

	while (*originalStr++)
		length++;

	dupStr = malloc(sizeof(char) * (length + 1));

	if (!dupStr)
		return (NULL);

	for (length++; length--;)
		dupStr[length] = *--originalStr;

	return (dupStr);
}
