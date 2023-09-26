#include "shellbuiltin.h"


/**
 * print_aliases - Prints alias key-value pairs.
 * @alias: Pointer to an alias_t structure.
 *
 * This function writes the alias key, "=", and value to
 * STDOUT, followed by a newline character.
 *
 * Return: None.
 */
void print_aliases(alias_t *alias)
{
	write(STDOUT_FILENO, alias->key, _strlen(alias->key));
	write(STDOUT_FILENO, "=", 2);
	write(STDOUT_FILENO, alias->value, _strlen(alias->value));
	write(STDOUT_FILENO, "\n", 2);
}

/**
 * add_alias - Adds or updates an alias in the list.
 * @alias: Pointer to a pointer to the alias_t list.
 * @name: The name of the alias to add or update.
 * @value: The value associated with the alias.
 *
 * Return: None.
 */
void add_alias(alias_t **alias, const char *name, const char *value)
{
	alias_t *shellalias = get_node(alias ? *alias : NULL, name);

	/*update an existing alias if found*/
	if (shellalias)
	{
		free_all(1, shellalias->value);
		shellalias->value = _strdup(value);
	}
	else
		add_dict_to_the_end(alias, name, value);
}

/**
 * _alias - Handles alias commands.
 * @info: Pointer to a store_info_t structure containing program
 * information.
 *
 * Return: The exit status of the function.
 */
int _alias(store_info_t *info)
{
	alias_t *alias;
	char *name, **argument = info->tokens + 1;
	ssize_t name_length;

	info->status = EXIT_SUCCESS;
	if (*argument)
	{
		do {
			name_length = _strchr(*argument, '=');

			if (name_length == -1)
			{
				alias = get_node(info->aliases, *argument);
				if (alias)
					print_aliases(alias);
				else
				{
					perrorl("Not found", info->tokens, *argument, NULL);
					info->status = EXIT_FAILURE;
				}
			}
			else
			{
				name = _strndup(*argument, name_length);
				add_alias(&info->aliases, name, *argument + name_length + 1);
				free_all(1, name);
			}
		} while (*++argument);
	}
	else
	{
		for (alias = info->aliases; alias; alias = alias->link)
			print_aliases(alias);
	}

	return (info->status);
}
