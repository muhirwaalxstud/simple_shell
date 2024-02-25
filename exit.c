#include "shell.h"

/**
 * _strncpy - Copies a string up to a specified length.
 * @dest: The destination string to copy to.
 * @src: The source string to copy from.
 * @n: The maximum number of characters to copy.
 *
 * This function copies at most 'n' characters from the source string 'src' to
 * the destination string 'dest'. If 'src' is shorter than 'n' characters, the
 * remainder of 'dest' will be filled with null bytes.
 *
 * Return: A pointer to the destination string 'dest'.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Concatenates two strings up to a specified length.
 * @dest: The destination string to concatenate to.
 * @src: The source string to concatenate from.
 * @n: The maximum number of characters to concatenate.
 *
 * This function appends at most the first 'n' characters from 'src' to the end
 * of the 'dest' string, overwriting the terminating null byte ('\0') at the
 * end of 'dest', then adds a terminating null byte. The strings may not overlap,
 * and 'dest' must have enough space for the result.
 *
 * Return: A pointer to the destination string 'dest'.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @s: The string to search within.
 * @c: The character to locate.
 *
 * This function searches for the first occurrence of the character 'c' (converted
 * to a char) in the string pointed to by 's'. The terminating null character
 * is considered part of the string; therefore, if 'c' is '\0', the function
 * locates the terminating null character. Returns a pointer to the located
 * character, or a null pointer if the character does not appear in the string.
 *
 * Return: A pointer to the located character, or NULL if the character does
 * not appear in the string.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

