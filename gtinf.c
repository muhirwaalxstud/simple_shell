#include "shell.h"

/**
 * clear_info - Initializes the fields of the info_t struct.
 * @info: Pointer to the info_t struct to be initialized.
 *
 * This function resets all fields of the info_t struct pointed to by 'info'.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes the info_t struct with provided arguments.
 * @info: Pointer to the info_t struct to be initialized.
 * @av: Argument vector containing command-line arguments.
 *
 * This function initializes the info_t struct pointed to by 'info' using the
 * command-line arguments provided in the argument vector 'av'. It sets the
 * 'fname' field to the name of the executable program. It then parses the
 * 'arg' field to extract individual command-line arguments and stores them
 * in the 'argv' field. Additionally, it updates the 'argc' field with the
 * number of command-line arguments.
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees dynamically allocated memory in the info_t struct.
 * @info: Pointer to the info_t struct.
 * @all: Flag indicating whether to free all fields or just argv-related fields.
 *
 * This function frees dynamically allocated memory in the info_t struct
 * pointed to by 'info'. If 'all' is true, it frees all fields including
 * 'env', 'history', 'alias', 'environ', and 'cmd_buf'. Otherwise, it only
 * frees 'argv' and 'arg' fields.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

