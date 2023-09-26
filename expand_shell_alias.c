#include "main.h"

/**
 * expand_alias_value - Expands alias references in a list of tokens.
 * @aliasList: The list of aliases.
 * @tokenPtr: A pointer to the array of tokens to process.
 *
 * Return: The name of the expanded alias, or NULL if no alias was expanded.
 */
char *expand_alias_value(alias_t *aliasList, char ***tokenPtr)
{
	char **aliasTokens, **tokens = *tokenPtr;

	if (!*tokens)
		return (NULL);

	while (aliasList)
	{
		if (!_strcmp(*tokens, aliasList->key))
		{
			aliasTokens = my_token(aliasList->value);
			*tokenPtr = merge_arrays(aliasTokens, tokens + 1);

			release_mem(&tokens);
			release_mem(&aliasTokens);

			return (aliasList->key);
		}
		aliasList = aliasList->link;
	}

	return (NULL);
}

/**
 * process_aliases - Processes and expands aliases in a list of tokens.
 * @aliasList: The list of aliases.
 * @token_ptr: A pointer to the array of tokens to process and expand.
 */
void process_aliases(alias_t *aliasList, char ***token_ptr)
{
	char **new, **old, *name, *value, *temp;

	if (!*token_ptr)
	{
		return;
		do {
			name = expand_alias_value(aliasList, token_ptr);
			value = get_value(aliasList, name);

			if (value && *value && _isspace(value[_strlen(value) - 1]))
			{
				old = *token_ptr;
				new = duplicateStringArray(old + 1);

				process_aliases(aliasList, &new);
				temp = *(old + 1);

				*(old + 1) = NULL;
				*token_ptr = merge_arrays(old, new);
				*(old + 1) = temp;

				release_mem(&old);
				release_mem(&new);
			}
		} while (name && **token_ptr && _strcmp(name, **token_ptr));
	}
}
