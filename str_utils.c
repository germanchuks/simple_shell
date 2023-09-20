#include "shell.h"

/**
 * isAlpha - Determines if a character is a letter of the alphabet.
 * @character: The character to evaluate.
 *
 * This function checks whether 'character' is a letter of the alphabet.
 *
 * Return: 1 if 'character' is an alphabet, 0 otherwise.
 */

int isAlpha(int character)
{
	if ((character >= 'a' && character <= 'z')
	|| (character >= 'A' && character <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * convToInt - Converts a string into an integer.
 * @str: The input string to be converted.
 *
 * This function takes a string 'str' and attempts to parse it into an integer.
 * If successful, it returns the integer value obtained from the string. If the
 * string does not represent a valid integer, it returns 0.
 *
 * Return: The integer value parsed from the string or 0 if not a valid
 * integer.
 */

int convToInt(char *str)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * handleInteractive - Checks if the shell is running in interactive mode.
 * @data: Pointer to information structure
 *
 * This function determines whether the shell is in interactive mode by
 * checking if the standard input (STDIN) is connected to a terminal and
 * if the 'readDescriptor' value is less than or equal to 2.
 *
 * Return: 1 if the shell in in interactive mode, or 0 if otherwise.
 */

int handleInteractive(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readDescriptor <= 2);
}

/**
 * isDelim - Checks if a character is a delimiter by comparing it to a
 * delimiter string.
 * @character: The characer to check.
 * @delimeter: The delimeter string to compare against.
 *
 * This function iterates through the characters in the 'delimiter' string
 * and checks if 'character' matches any of them.
 *
 * Return: 1 if the character is a delimeter, 0 if otherwise.
 */

int isDelim(char character, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == character)
			return (1);
	return (0);
}
