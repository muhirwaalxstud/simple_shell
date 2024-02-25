#include "shell.h"

/**
 * input_buf - Buffers chained commands from standard input.
 * @info: Pointer to the parameter struct.
 * @buf: Address of the buffer to store the input.
 * @len: Address of the length variable.
 *
 * This function reads input from standard input and buffers chained commands
 * delimited by semicolons (';'). It fills the buffer pointed to by 'buf' with
 * input read from standard input until a semicolon is encountered or until the
 * buffer is full. If a newline character ('\n') is encountered, it is removed
 * and the input is added to the history list. The 'len' variable holds the
 * length of the buffer.
 *
 * Return: The number of bytes read from standard input.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* Check if buffer is empty */
	{
		free(*buf); /* Free previously allocated memory */
		*buf = NULL;
		signal(SIGINT, sigintHandler); /* Block SIGINT signals */
		r = getline(buf, &len_p, stdin); /* Read input from standard input */
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Remove trailing newline */
				r--;
			}
			info->linecount_flag = 1; /* Set flag for command line count */
			remove_comments(*buf); /* Remove comments from input */
			build_history_list(info, *buf, info->histcount++); /* Add input to history list */
			/* Check if input contains a command chain */
			{
				*len = r; /* Update length variable */
				info->cmd_buf = buf; /* Store buffer address */
			}
		}
	}
	return (r);
}

/**
 * get_input - Gets a line of input from the buffer.
 * @info: Pointer to the parameter struct.
 *
 * This function retrieves a line of input from the buffer containing chained
 * commands. It iterates through the buffer, handling command chaining, and
 * returns the current command line without the newline character. It updates
 * the 'info->arg' pointer to point to the current command line.
 *
 * Return: The length of the current command line.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* Buffer for chained commands */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH); /* Flush the output buffer */
	r = input_buf(info, &buf, &len); /* Read input from buffer */
	if (r == -1) /* Handle EOF */
		return (-1);
	if (len) /* Check if there are commands left in the buffer */
	{
		j = i; /* Initialize new iterator to current buffer position */
		p = buf + i; /* Get pointer for return */

		check_chain(info, buf, &j, i, len); /* Check for command chaining */
		while (j < len) /* Iterate to semicolon or end of buffer */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past null terminator */
		if (i >= len) /* Check if end of buffer is reached */
		{
			i = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM; /* Set buffer type to normal */
		}

		*buf_p = p; /* Pass back pointer

