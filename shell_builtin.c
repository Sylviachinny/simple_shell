#include "shellbuiltin.h"

/**
 * get_builtin - Retrieves a pointer to a built-in function by name.
 * @name: The name of the built-in function to retrieve.
 *
 * Return: A pointer to the built-in function if found, otherwise NULL.
 */
const builtin_t *get_builtin(const char *name)
{
	const builtin_t *builtin = NULL;
	const builtin_t *temp = NULL;

	static builtin_t builtins[] = {
		{"cd", _cd},
		{"env", _env},
		{"exec", _exec},
		{"exit", _exit_s},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{0}
	};

	for (temp = builtins; temp->name; temp += 1)
	{
		builtin = temp;
		if (_strcmp(name, builtin->name) == 0)
		{
			return (builtin);
		}
	}
	return (NULL);
}
