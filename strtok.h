#ifndef _STRTOK_H_
#define _STRTOK_H_

#include <stdlib.h>
#include "myqoute.h"
#include "utilities.h"
#include "shellhelpertype.h"

/**
 * struct strtok - Represents state for a string tokenization process.
 * @tokens: A pointer to an array of token strings.
 * @store_tok: A pointer to the original string being tokenized.
 * @state: The current state of tokenization, including quotes.
 */
struct strtok
{
	char **tokens;
	const char *store_tok;
	quote_state state;
};

size_t tok_counter(const char *s);
char **my_token(const char *tok);
void release_mem(char ***str);
char **arrdup(char **arr);

#endif /*_STRTOK_H_*/
