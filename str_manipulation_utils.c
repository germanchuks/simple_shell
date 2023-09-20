#include "shell.h"

/**
 * cmpStr - Compare two strings lexicographically.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 *
 * Return: Negative value if str1 < str2, positive value if str1 > str2,
 * 0 if str1 == str2.
 */

int cmpStr(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * concatStr - Concatenates two strings.
 * @destBuffer: The destination buffer.
 * @srcBuffer: The source buffer.
 *
 * Return: A pointer to the destination buffer.
 */

char *concatStr(char *destBuffer, char *srcBuffer)
{
	char *result = destBuffer;

	while (*destBuffer)
		destBuffer++;

	while (*srcBuffer)
		*destBuffer++ = *srcBuffer++;

	*destBuffer = *srcBuffer;

	return (result);
}

/**
 * strLength - Computes the length of a string.
 * @str: The input string to measure.
 *
 * Return: The length of the string in int.
 */

int strLength(char *str)
{
	int length = 0;

	while (*str != '\0')
	{
		length++;
		str++;
	}

	return (length);
}

/**
 * findPrefix - Check if a string starts with a specified substring.
 * @string: The string to search within.
 * @substring: The substring to find at the beginning of the string.
 *
 * Return: Pointer to the next character of the string if the substring
 * is found, or NULL otherwise.
 */

char *findPrefix(const char *string, const char *substring)
{
	while (*substring)
	{
		if (*substring++ != *string++)
			return (NULL);
	}

	return ((char *)string);
}
