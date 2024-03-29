#include "shell.h"

/**
 * _eputs - Prints a string to the standard error.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        _eputchar(str[i]);
        i++;
    }
}

/**
 * _eputchar - Writes the character 'c' to the standard error.
 * @c: The character to be printed.
 *
 * Return: On success, returns 1.
 *         On error, returns -1 and sets errno appropriately.
 */
int _eputchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * _putfd - Writes the character 'c' to the given file descriptor.
 * @c: The character to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, returns 1.
 *         On error, returns -1 and sets errno appropriately.
 */
int _putfd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * _putsfd - Prints a string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int _putsfd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += _putfd(*str++, fd);
    }
    return (i);
}

