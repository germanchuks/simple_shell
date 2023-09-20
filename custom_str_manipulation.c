#include "shell.h"

/**
 * findChar - Custom implementation of strchr function.
 * @string: The string to be examined.
 * @character: The character to search for.
 *
 * This function customizes the behavior of the strchr function by searching
 * for the first occurrence of @character within @string.
 *
 * Return: A pointer to the first occurrence of @character in @string,
 * or NULL if 'character' is not found.
 */

char *findChar(char *string, char character)
{
	do {
		if (*string == character)
			return (string);
	} while (*string++ != '\0');

	return (NULL);
}

/**
 * copySubstr - Custom version of strncpy function.
 * @destString: The string where data is copied to.
 * @srcString: The string from which data is copied.
 * @maxChar: The maximum number of characters to copy, including the null byte.
 *
 * This function provides a customized implementation of the strncpy function.
 * It copies up to @maxChar characters from @srcString to @destString.
 *
 * Return: A pointer to the destination string after copying.
 */

char *copySubstr(char *destString, char *srcString, int maxChar)
{
	char *destStart = destString;
	int srcIndex, destIndex;

	srcIndex = 0;
	while (srcString[srcIndex] != '\0' && srcIndex < maxChar - 1)
	{
		destString[srcIndex] = srcString[srcIndex];
		srcIndex++;
	}

	if (srcIndex < maxChar)
	{
		destIndex = srcIndex;
		while (destIndex < maxChar)
		{
			destString[destIndex] = '\0';
			destIndex++;
		}
	}

	return (destStart);
}

/**
 * concatSubstr - Custom implementation of strncat.
 * @destString: The first string to concatenate to.
 * @srcString: The second string to concatenate.
 * @maxBytes: The maximum number of bytes to be used for concatenation.
 *
 * This function appends up to @maxBytes characters from @srcString to the end
 * of @destString, ensuring that the result is null-terminated.
 *
 * Return: A pointer to the concatenated string.
 */

char *concatSubstr(char *destString, char *srcString, int maxBytes)
{
	int destIndex = 0;
	int srcIndex = 0;
	char *result = destString;

	while (destString[destIndex] != '\0')
		destIndex++;

	while (srcString[srcIndex] != '\0' && srcIndex < maxBytes)
	{
		destString[destIndex] = srcString[srcIndex];
		destIndex++;
		srcIndex++;
	}

	if (srcIndex < maxBytes)
		destString[destIndex] = '\0';

	return (result);
}
