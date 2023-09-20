#include "shell.h"

/**
 * printStrToDesc - Writes the provided string to a specified file descriptor.
 * @string: The string to be written.
 * @fileDescriptor: The file descriptor to write to.
 *
 * This function writes the characters from @string' to the specified
 * @fileDescriptor.
 *
 * Return: The number of characters written.
 */

int printStrToDesc(char *string, int fileDescriptor)
{
	int charsWritten = 0;

	if (!string)
		return (0);

	while (*string)
	{
		charsWritten += printCharToDesc(*string++, fileDescriptor);
	}

	return (charsWritten);
}

/**
 * printErrStr - Prints an error message string.
 * @errorMsg: The error message to be printed.
 *
 * This function is responsible for printing an error message,
 * character by character, to the standard error stream.
 *
 * Return: Nothing.
 */

void printErrStr(char *errorMsg)
{
	int index = 0;

	if (!errorMsg)
		return;

	while (errorMsg[index] != '\0')
	{
		printErrChar(errorMsg[index]);
		index++;
	}
}

/**
 * printErrChar - Writes the character to stderr.
 * @character: The character to write.
 *
 * This function writes a character to the standard error (stderr).
 * If @character is equal to the FLUSH_BUFFER_FLAG or the buffer is full,
 * it flushes the buffer to stderr.
 *
 * Return: 1 on success,-1 if error occurs, and set the appropriate error code
 * to errno.
 */

int printErrChar(char character)
{
	static int index;
	static char outputBuf[WRITE_BUFFER_SIZE];

	if (character == FLUSH_BUFFER_FLAG || index >= WRITE_BUFFER_SIZE)
	{
		write(2, outputBuf, index);
		index = 0;
	}
	if (character != FLUSH_BUFFER_FLAG)
		outputBuf[index++] = character;
	return (1);
}

/**
 * printCharToDesc - Writes a single character to a specified file descriptor.
 * @character: The character to be written.
 * @fileDescriptor: The file descriptor to which the character is written.
 *
 * This function writes the provided @character to the specified
 * @fileDescriptor.
 *
 * Return: 1 on success,-1 if error occurs, and set the appropriate error code
 * to errno.
 */

int printCharToDesc(char character, int fileDescriptor)
{
	static int index;
	static char outputBuf[WRITE_BUFFER_SIZE];

	if (character == FLUSH_BUFFER_FLAG || index >= WRITE_BUFFER_SIZE)
	{
		write(fileDescriptor, outputBuf, index);
		index = 0;
	}
	if (character != FLUSH_BUFFER_FLAG)
		outputBuf[index++] = character;
	return (1);
}
