#ifndef _SHELLBUILTIN_H_
#define _SHELLBUILTIN_H_

#include "limits.h"
#include <stdlib.h>
#include <unistd.h>

#include "shellenv.h"
#include "handlerror.h"
#include "shell.h"
#include "shellpath.h"
#include "utilities.h"
#include "shellhelpertype.h"


typedef int (*builtin_handler)(store_info_t *);

/**
 * struct built_in - builtin command
 * @name: command name
 * @built_f: function to call
 * @help: command usage
 * @dsc: command description
 */
struct built_in
{
	const char *name;
	builtin_handler built_f;
	/*const char *help;
	const char *dsc;*/
};

const builtin_t *get_builtin(const char *name);

int _cd(store_info_t *info);
int _env(store_info_t *info);
int _exec(store_info_t *info);
int _exit_s(store_info_t *info);
int _setenv(store_info_t *info);
int _unsetenv(store_info_t *info);

/**
 * struct atoi - A custom data structure for parsing integers
 * character by character.
 * @num: The accumulated integer value.
 * @curr_digit: The current digit being processed.
 * @iterator: The index of the current character being processed.
 */
typedef struct atoi
{
	unsigned int num;
	unsigned int curr_digit;
	size_t iterator;
} atoi_t;
#endif /*_SHELLBUILTIN_H_*/
