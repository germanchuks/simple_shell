#include "shell.h"

/**
 * errStrToInt - Converts a string to an integer.
 * @inputStr: The string to be converted.
 *
 * This function attempts to convert a string into an integer.
 *
 * Return: The integer value if successful, -1 on error or 0 if no numbers
 * are found.
 */

int errStrToInt(char *inputStr)
{
	unsigned long int result = 0;
	int index = 0;

	if (*inputStr == '+')
		inputStr++;

	for (index = 0; inputStr[index] != '\0'; index++)
	{
		if (inputStr[index] >= '0' && inputStr[index] <= '9')
		{
			result *= 10;
			result += (inputStr[index] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (result);
}

/**
 * printShellErr - Displays a shell error message.
 * @data: Pointer to the data_t struct containing shell information.
 * @errorMessage: The error message to be printed.
 *
 * This function displays a shell error message specified @errorMessage.
 *
 * Return: Nothing.
 */

void printShellErr(data_t *data, char *errorMessage)
{
	printErrStr(data->fName);
	printErrStr(": ");
	printDecimal(data->lineCounter, STDERR_FILENO);
	printErrStr(": ");
	printErrStr(data->argv[0]);
	printErrStr(": ");
	printErrStr(errorMessage);
}

/**
 * printDecimal - Writes an integer (decimal number) to a file descriptor.
 * @input: The integer to be written.
 * @fileDescriptor: The file descriptor to which the integer is written.
 *
 * This function writes the provided integer @input to the specified file
 * descriptor.
 *
 * Return: The number of characters written.
 */

int printDecimal(int input, int fileDescriptor)
{
	int (*printCharFunc)(char) = putChar;
	int index, count = 0;
	unsigned int absValue, currentDigit;

	if (fileDescriptor == STDERR_FILENO)
		printCharFunc = printErrChar;

	if (input < 0)
	{
		absValue = -input;
		printCharFunc('-');
		count++;
	}
	else
	{
		absValue = input;
	}

	currentDigit = absValue;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (absValue / index)
		{
			printCharFunc('0' + currentDigit / index);
			count++;
		}
		currentDigit %= index;
	}

	printCharFunc('0' + currentDigit);
	count++;

	return (count);
}

/**
 * removeComments - Replaces the first instance of '#' with '\0' in a string.
 * @str: The address of the string to modify.
 *
 * This function searches for the first occurrence of the '#' character
 * in the string pointed to by 'str' and replaces it with a null
 * terminator '\0'.
 *
 * Return: 0 (Always).
 */

void removeComments(char *str)
{
	int index;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] == '#' && (!index || str[index - 1] == ' '))
		{
			str[index] = '\0';
			break;
		}
	}
}

/**
 * convertNum - Converts a long integer to a string representation.
 * @number: The number to be converted.
 * @convBase: The base for conversion.
 * @argFlags: Argument argFlags.
 *
 * This function converts the long integer @number into a string representation
 * with the specified base.
 *
 * Return: The string representation of the number.
 */

char *convertNum(long int number, int convBase, int argFlags)
{
	static char *digitArray;
	static char buffer[50];
	unsigned long absNum = number;
	char signChar = 0;
	char *outputPtr;

	if (!(argFlags & CONVERT_TO_UNSIGNED) && number < 0)
	{
		absNum = -number;
		signChar = '-';
	}

	digitArray = argFlags
		& CONVERT_TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	outputPtr = &buffer[49];
	*outputPtr = '\0';

	do {
		*--outputPtr = digitArray[absNum % convBase];
		absNum /= convBase;
	} while (absNum != 0);

	if (signChar)
		*--outputPtr = signChar;

	return (outputPtr);
}
