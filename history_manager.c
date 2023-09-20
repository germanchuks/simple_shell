#include "shell.h"

/**
 * generateHistPath - Generate the path to the history file.
 * @data: Pointer to the parameter struct.
 *
 * This function constructs the path to the history file by combining the
 * home directory 'hDir' and the specified history file name 'H_FILE'.
 *
 * Return: Allocated string containing the history file path, otherwise NULL.
 */

char *generateHistPath(data_t *data)
{
	char *hDir = getEnvironVar(data, "HOME");
	char *hPath;

	if (!hDir)
		return (NULL);

	hPath = malloc(sizeof(char) * (strLength(hDir) + strLength(H_FILE) + 2));
	if (!hPath)
		return (NULL);

	hPath[0] = 0;
	copyStr(hPath, hDir);
	concatStr(hPath, "/");
	concatStr(hPath, H_FILE);

	return (hPath);
}

/**
 * updateHistory - Updates the entry numbers in the history linked list..
 * @data: The structure containing relevant arguments.
 *
 * This function updates the number field in each history entry to reflect the
 * new order after any changes have been made.
 *
 * Return: The updated history entry count.
 */

int updateHistory(data_t *data)
{
	item_t *currentNode = data->historyList;
	int index = 0;

	while (currentNode)
	{
		currentNode->number = index++;
		currentNode = currentNode->next;
	}

	return (data->historyCounter = index);
}

/**
 * saveHistoryToFile - Writes the command history to a file.
 * @data: Pointer to the parameter struct.
 *
 * This function writes the command history to a file specified by the 'data'
 * parameter. It creates or truncates the file and writes each history entry
 * followed by a newline character.
 *
 * Return: 1 on success, -1 on failure.
 */

int saveHistoryToFile(data_t *data)
{
	ssize_t fileDesc;
	char *filename = generateHistPath(data);
	item_t *node = NULL;

	if (!filename)
		return (-1);

	fileDesc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fileDesc == -1)
		return (-1);

	for (node = data->historyList; node; node = node->next)
	{
		printStrToDesc(node->string, fileDesc);
		printCharToDesc('\n', fileDesc);
	}

	printCharToDesc(FLUSH_BUFFER_FLAG, fileDesc);
	close(fileDesc);
	return (1);
}

/**
 * loadHistoryFromFile - Load command history from a file into the data
 * structure.
 * @data: Pointer to the parameter struct.
 *
 * This function reads command history entries from a file specified by @data
 * parameter and populates the history list.
 *
 * Return: The number of history entries loaded, or 0 on failure.
 */

int loadHistoryFromFile(data_t *data)
{
	int index, linesRead = 0, linesCount = 0;
	ssize_t fileDesc, bytesRead, fileSize = 0;
	struct stat fileStat;
	char *fileContent = NULL, *filename = generateHistPath(data);

	if (!filename)
		return (0);
	fileDesc = open(filename, O_RDONLY);
	free(filename);
	if (fileDesc == -1)
		return (0);
	if (!fstat(fileDesc, &fileStat))
		fileSize = fileStat.st_size;
	if (fileSize < 2)
		return (0);
	fileContent = malloc(sizeof(char) * (fileSize + 1));
	if (!fileContent)
		return (0);
	bytesRead = read(fileDesc, fileContent, fileSize);
	fileContent[fileSize] = 0;
	if (bytesRead <= 0)
		return (free(fileContent), 0);
	close(fileDesc);
	for (index = 0; index < fileSize; index++)
	{
		if (fileContent[index] == '\n')
		{
			fileContent[index] = 0;
			addToHistoryList(data, fileContent + linesRead, linesCount++);
			linesRead = index + 1;
		}
	}
	if (linesRead != index)
		addToHistoryList(data, fileContent + linesRead, linesCount++);
	free(fileContent);
	data->historyCounter = linesCount;
	while (data->historyCounter-- >= MAX_HISTORY_SIZE)
		removeNodeAtIdx(&(data->historyList), 0);
	updateHistory(data);
	return (data->historyCounter);
}

/**
 * addToHistoryList - Adds a new command entry to the history linked list.
 * @data: A structure containing relevant arguments.
 * @command: The command entry to be added to the history list.
 * @lineNum: The line number associated with this command entry.
 *
 * This function appends a new command entry, along with its line number, to
 * the history linked list.
 *
 * Return: 0 (Always).
 */

int addToHistoryList(data_t *data, char *command, int lineNum)
{
	item_t *newNode = NULL;

	if (data->historyList)
		newNode = data->historyList;

	appendNodeToList(&newNode, command, lineNum);

	if (!data->historyList)
		data->historyList = newNode;

	return (0);
}
