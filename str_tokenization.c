#include "shell.h"

/**
 * strTokenize - Splits a string into words, ignoring repeated delimiters.
 * @inStr: The input string to be split.
 * @delim: The delimiter string used for splitting.
 *
 * This function splits the @inputString into words using the @delimiter
 * while ignoring repeated delimiters.
 *
 * Return: A pointer to an array of strings, or NULL on error.
 */

char **strTokenize(char *inStr, char *delim)
{
	int inIdx, idxTok, tokLen, charIdx, numToks = 0;
	char **tokens;

	if (inStr == NULL || inStr[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (inIdx = 0; inStr[inIdx] != '\0'; inIdx++)
	{
		if (!isDelim(inStr[inIdx], delim) && (isDelim(inStr[inIdx + 1], delim)
			|| !inStr[inIdx + 1]))
			numToks++;
	}

	if (numToks == 0)
		return (NULL);
	tokens = malloc((1 + numToks) * sizeof(char *));
	if (!tokens)
		return (NULL);
	for (inIdx = 0, idxTok = 0; idxTok < numToks; idxTok++)
	{
		while (isDelim(inStr[inIdx], delim))
			inIdx++;
		tokLen = 0;
		while (!isDelim(inStr[inIdx + tokLen], delim) && inStr[inIdx + tokLen])
			tokLen++;
		tokens[idxTok] = malloc((tokLen + 1) * sizeof(char));
		if (!tokens[idxTok])
		{
			for (tokLen = 0; tokLen < idxTok; tokLen++)
				free(tokens[tokLen]);
			free(tokens);
			return (NULL);
		}
		for (charIdx = 0; charIdx < tokLen; charIdx++)
			tokens[idxTok][charIdx] = inStr[inIdx++];
		tokens[idxTok][charIdx] = 0;
	}
	tokens[idxTok] = NULL;
	return (tokens);
}

/**
 * strTokenizeDel - Splits a string into words based on a specified delimiter
 * character.
 * @inStr: The input string to be split.
 * @delim: The delimiter character used for splitting.
 *
 * This function splits the @inStr into words using the specified
 * @delim character, and treats repeated occurences as separate
 * delimeters.
 *
 * Return: A pointer to an array of strings, or NULL otherwise.
 */

char **strTokenizeDel(char *inStr, char delim)
{
	int inIdx, idxTok, tokLen, charIdx, numToks = 0;
	char **tokens;

	if (inStr == NULL || inStr[0] == 0)
		return (NULL);
	for (inIdx = 0; inStr[inIdx] != '\0'; inIdx++)
		if ((inStr[inIdx] != delim && inStr[inIdx + 1] == delim)
		|| (inStr[inIdx] != delim && !inStr[inIdx + 1])
		|| inStr[inIdx + 1] == delim)
			numToks++;
	if (numToks == 0)
		return (NULL);
	tokens = malloc((1 + numToks) * sizeof(char *));
	if (!tokens)
		return (NULL);
	for (inIdx = 0, idxTok = 0; idxTok < numToks; idxTok++)
	{
		while (inStr[inIdx] == delim && inStr[inIdx] != delim)
			inIdx++;
		tokLen = 0;
		while (inStr[inIdx + tokLen] != delim && inStr[inIdx + tokLen]
			&& inStr[inIdx + tokLen] != delim)
			tokLen++;
		tokens[idxTok] = malloc((tokLen + 1) * sizeof(char));
		if (!tokens[idxTok])
		{
			for (tokLen = 0; tokLen < idxTok; tokLen++)
				free(tokens[tokLen]);
			free(tokens);
			return (NULL);
		}
		for (charIdx = 0; charIdx < tokLen; charIdx++)
			tokens[idxTok][charIdx] = inStr[inIdx++];
		tokens[idxTok][charIdx] = 0;
	}
	tokens[idxTok] = NULL;
	return (tokens);
}
