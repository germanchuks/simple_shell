#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

#define H_FILE ".simple_shell_history"
#define MAX_HISTORY_SIZE 4096

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define FLUSH_BUFFER_FLAG -1

#define NORMAL_COMMAND 0
#define OR_COMMAND 1
#define AND_COMMAND 2
#define CHAIN_COMMAND 3

#define USE_SYSTEM_STRTOK 0
#define USE_SYSTEM_GETLINE 0

/**
 * struct item_t - Represents an element in a singly linked list of strings.
 * @number: Numeric identifier for the item.
 * @string: The string data stored in the item.
 * @next: Pointer to the next item in the linked list.
 *
 * This structure defines an individual element within a singly linked list of
 * strings. It includes an integer identifier, the string value it holds, and
 * a pointer to the next item in the list.
 */
typedef struct item_t
{
	char *string;
	int number;
	struct item_t *next;
} item_t;

/**
 * struct data_t - Structure for holding various command-related information.
 * @arg: Command arguments as a string.
 * @argc: Number of command arguments.
 * @argv: Array of command argument strings.
 * @commandPath: Path to the current command.
 * @execStat: Status code from the last executed command.
 * @cmdBuf: Pointer to a command buffer for chaining commands.
 * @cmdBufType: Type of command separator (e.g., ||, &&, or ;).
 * @readDescriptor: File descriptor for reading input.
 * @historyCounter: Counter for command history line numbers.
 * @lineCounter: Current line number.
 * @fName: Name of the program file.
 * @errorCode: Error code for exit() calls.
 * @lineCounterFlag: Flag to indicate line counting.
 * @envList: Linked list for storing environment variables.
 * @historyList: Linked list for storing command history.
 * @aliasList: Linked list for storing aliases.
 * @environ: Array of custom-modified environment variables.
 * @envChanged: Flag indicating if the environment was altered.
 */
typedef struct data_t
{
	char *arg;
	char **argv;
	char *commandPath;
	int argc;
	int execStat;
	int readDescriptor;
	int historyCounter;
	unsigned int lineCounter;
	int cmdBufType;
	int errorCode;
	int lineCounterFlag;
	char *fName;
	char **cmdBuf;
	item_t *envList;
	item_t *historyList;
	item_t *aliasList;
	char **environ;
	int envChanged;
} data_t;

/**
 * struct BuiltinCommand - Defines a built-in command and its corresponding
 * action.
 * @command: The name of the built-in command.
 * @function: A function pointer pointing to the command's execution function.
 *
 * This structure associates a built-in command's name with its respective
 * handling function.
 */
typedef struct BuiltinCommand
{
	char *command;
	int (*function)(data_t *);
} BuiltinCommand;

/* Initializes a struct data_t with default values. */
#define INIT_SHELL_INFO															\
	{																			\
		NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL,	\
			NULL, 0																\
	}

extern char **environ;

/* Linked list handler functions */
size_t getListLen(const item_t *);
char **itemListToArr(item_t *);
size_t displayStrList(const item_t *);
item_t *findNodeWithPrefix(item_t *, char *, char);
ssize_t findNodeIndex(item_t *, item_t *);

/* Linked list handler functions 2*/
item_t *prependNodeToList(item_t **, const char *, int);
item_t *appendNodeToList(item_t **, const char *, int);
size_t displayList(const item_t *);
int removeNodeAtIdx(item_t **, unsigned int);
void freeLinkedList(item_t **);

/* Custom String Functions 1 */
int strLength(char *);
int cmpStr(char *, char *);
char *findPrefix(const char *, const char *);
char *concatStr(char *, char *);

/* Custom String functions 2 */
char *copyStr(char *, char *);
char *dupStr(const char *);
void putStr(char *);
int putChar(char);

/* String Utilities 1 */
int handleInteractive(data_t *data);
int isDelim(char, char *);
int isAlpha(int);
int convToInt(char *);

/* String Utilities 2 */
char *copySubstr(char *, char *, int);
char *concatSubstr(char *, char *, int);
char *findChar(char *, char);

/* Error handling functions */
void printErrStr(char *);
int printErrChar(char);
int printCharToDesc(char, int);
int printStrToDesc(char *str, int descriptor);

/* Error handling functions 2 */
void printShellErr(data_t *, char *);
int errStrToInt(char *);
int printDecimal(int, int);
char *convertNum(long int, int, int);
void removeComments(char *);

/* Variable substitution functions */
int expandCmdAlias(data_t *);
int expandVariables(data_t *);
int isCommandChained(data_t *, char *, size_t *);
void handleCommandChaining(data_t *, char *, size_t *, size_t, size_t);
int updateStrPtr(char **, char *);

/* Built-in command functions */
int exitShell(data_t *);
int changeDir(data_t *);
int dispHelp(data_t *);

/* Built-in command  functions 2 */
int dispHistory(data_t *);
int manageAlias(data_t *);

/* Memory Utilities */
void freeStrArr(char **);
void *memRealloc(void *, unsigned int, unsigned int);
char *fillMemWithByte(char *, char, unsigned int);

/* Free Memory Function */
int freePointer(void **);

/* Shell loop functions */
void createChildProcessAndExec(data_t *);
int runShell(data_t *, char **);
int searchAndExecBuiltin(data_t *);
void locateAndExecCmd(data_t *);

/* Environment Operation Handlers */
int rmvEnvVar(data_t *, char *);
int initEnvVar(data_t *, char *, char *);
char **getEnv(data_t *);

/* Environment Utilities */
char *getEnvironVar(data_t *, const char *);
int displayEnv(data_t *);
int initEnvironVar(data_t *);
int rmvEnvironVar(data_t *);
int initEnvList(data_t *);

/* Command Utilities */
int isBuiltinCommand(data_t *, char *);
char *copyCharacters(char *, int, int);
char *findCmdInPath(data_t *, char *, char *);

/* Custom String Tokenizer Functions */
char **strTokenize(char *, char *);
char **strTokenizeDel(char *, char);

/* Getline functions */
ssize_t getInput(data_t *);
int getLine(data_t *, char **, size_t *);
void handleSignalInterrupt(int);

/* Get shell information functions */
void initShellData(data_t *, char **);
void freeShellData(data_t *, int);
void clearShellData(data_t *);

/* History management functions */
int updateHistory(data_t *data_t);
int addToHistoryList(data_t *data_t, char *buffer, int lineCount);
int saveHistoryToFile(data_t *data_t);
int loadHistoryFromFile(data_t *data_t);
char *generateHistPath(data_t *data_t);

#endif /* SHELL_H */
