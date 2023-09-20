#include "shell.h"

/**
 * readInputBuffer - Read and buffer input, handling chained commands.
 * @data: Pointer to the data_t struct.
 * @buffer: The address of the buffer to store the input.
 * @bufferSize: The address of the buffer size.
 *
 * This function reads input from stdin, processes it, and handles chained
 * commands by buffering them. It also handles signal interruptions.
 *
 * Return: The number of bytes read.
 */

ssize_t readInputBuffer(data_t *data, char **buffer, size_t *bufferSize)
{
	size_t bufferSize_ptr = 0;
	ssize_t bytesRead = 0;

	if (!*bufferSize)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handleSignalInterrupt);
#if USE_SYSTEM_GETLINE
		bytesRead = getline(buffer, &bufferSize_ptr, stdin);
#else
		bytesRead = getLine(data, buffer, &bufferSize_ptr);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			data->lineCounterFlag = 1;
			removeComments(*buffer);
			addToHistoryList(data, *buffer, data->historyCounter++);

			if (isCommandChained(data, *buffer, bufferSize))
			{
				*bufferSize = bytesRead;
				data->cmdBuf = buffer;
			}
		}
	}
	return (bytesRead);
}

/**
 * getInput - Read and process user input, handling command chaining.
 * @data: Pointer to the data_t struct.
 *
 * This function reads and processes user input, handling command chaining.
 * It returns the number of bytes read, excluding newline characters.
 *
 * Return: The number of bytes read.
 */

ssize_t getInput(data_t *data)
{
	static size_t currPos, startPos;
	static size_t length;
	ssize_t bytesRead = 0;
	char **cmdBuf_ptr = &(data->arg);
	static char *cmdBuf;
	char *pos;

	printCharToDesc(FLUSH_BUFFER_FLAG, data->readDescriptor);
	bytesRead = readInputBuffer(data, &cmdBuf, &length);
	if (bytesRead == -1)
		return (-1);
	if (length)
	{
		startPos = currPos;
		pos = cmdBuf + currPos;

		handleCommandChaining(data, cmdBuf, &startPos, currPos, length);
		while (startPos < length)
		{
			if (isCommandChained(data, cmdBuf, &startPos))
				break;
			startPos++;
		}

		currPos = startPos + 1;
		if (currPos >= length)
		{
			currPos = length = 0;
			data->cmdBufType = NORMAL_COMMAND;
		}

		*cmdBuf_ptr = pos;
		return (strLength(pos));
	}

	*cmdBuf_ptr = cmdBuf;
	return (bytesRead);
}

/**
 * readBuffer - Read data from a file descriptor into a buffer.
 * @data: Pointer to the data_t struct.
 * @buffer: The buffer to store the read data.
 * @sizeRead: Pointer to the variable holding the size of data read.
 *
 * This function reads data from a specified file descriptor into the provided
 * buffer. It updates the size of data read in the 'sizeRead' variable.
 *
 * Return: The number of bytes read.
 */

ssize_t readBuffer(data_t *data, char *buffer, size_t *sizeRead)
{
	ssize_t bytesRead = 0;

	if (*sizeRead)
		return (0);
	bytesRead = read(data->readDescriptor, buffer, READ_BUFFER_SIZE);
	if (bytesRead >= 0)
		*sizeRead = bytesRead;
	return (bytesRead);
}

/**
 * getLine - Reads the next line of input from STDIN.
 * @data: Pointer to the data_t struct.
 * @bufferPtr: Address of a pointer to a buffer, which can be preallocated or
 * NULL.
 * @bufferSize: Size of the preallocated buffer if not NULL.
 *
 * This function reads the next line of input from STDIN, dynamically managing
 * the buffer to accommodate variable line lengths.
 *
 * Return: The number of bytes read.
 */

int getLine(data_t *data, char **bufferPtr, size_t *bufferSize)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t currPos, bufferLen;
	ssize_t bytes = 0, resBytes = 0;
	char *inBuf = NULL, *newInBuf = NULL, *newLinePos;
	size_t itr;

	inBuf = *bufferPtr;
	if (inBuf && bufferSize)
		resBytes = *bufferSize;
	if (currPos == bufferLen)
		currPos = bufferLen = 0;

	bytes = readBuffer(data, buffer, &bufferLen);
	if (bytes == -1 || (bytes == 0 && bufferLen == 0))
		return (-1);

	newLinePos = findChar(buffer + currPos, '\n');
	itr = newLinePos ? 1 + (unsigned int)(newLinePos - buffer) : bufferLen;
	newInBuf = memRealloc(inBuf, resBytes, inBuf ? resBytes + itr : itr + 1);
	if (!newInBuf)
		return (inBuf ? (free(inBuf), -1) : -1);

	if (resBytes)
		concatSubstr(newInBuf, buffer + currPos, itr - currPos);
	else
		copySubstr(newInBuf, buffer + currPos, itr - currPos + 1);

	resBytes += itr - currPos;
	currPos = itr;
	inBuf = newInBuf;

	if (bufferSize)
		*bufferSize = resBytes;
	*bufferPtr = inBuf;
	return (resBytes);
}

/**
 * handleSignalInterrupt - Handle the SIGINT signal (Ctrl-C) by
 * resetting the prompt.
 * @signalNum: The signal number (unused).
 *
 * Return: Nothing.
 */

void handleSignalInterrupt(__attribute__((unused)) int signalNum)
{
	putStr("\n");
	putStr("$ ");
	putChar(FLUSH_BUFFER_FLAG);
}
