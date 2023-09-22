#ifndef _MYQUOTE_H_
#define _MYQUOTE_H_

#include <stdlib.h>
#include <stdbool.h>
#include "utilities.h"

/**
 * enum quote - enumerating quote
 * @QUOTE_NONE: none quote
 * @QUOTE_WORD: quote word
 * @QUOTE_DOUBLE: quote double
 * @QUOTE_SINGLE: quote single
 * @QUOTE_ESCAPE:quote escape
 */
typedef enum quote
{
	QUOTE_NONE   = 0x0,
	QUOTE_WORD   = 0x1,
	QUOTE_DOUBLE = 0x2,
	QUOTE_SINGLE = 0x4,
	QUOTE_ESCAPE = 0x8
} quote_state;

typedef size_t (*quote_state_fp)(const char *, quote_state *);

quote_state_fp quote_factory(quote_state str);
quote_state quote_proc(char c);

size_t quote_double(const char *str, quote_state *state);
size_t quote_single(const char *str, quote_state *state);
size_t quote_escape(const char *str, quote_state *state);
size_t quote_none(const char *str, quote_state *state);
size_t quote_word(const char *str, quote_state *state);
size_t quote_str_len(const char *str, quote_state state);

/********SHELL QUOTE UTILITIES********/
/*int _isspecial_double(char c);*/
int is_double_quote_escape(char c);
bool _isspace(int c);
bool _isquote(int c);
/*bool _isnumber(const char *s);*/
bool is_numeric(const char *str);
bool _isident(int c);
bool _isdigit(int c);
bool _isalpha(int c);
bool _isalnum(int c);

/**
 * struct dequote - Represents the state of a dequoting operation.
 * @new: Pointer to the dequoted string.
 * @length: Length of the dequoted string.
 * @the_state_len: Length of the state information.
 * @q_state: The current state of quoting within the dequoted string.
 *
 * Description: This structure is used to keep track of the state
 * of a dequoting operation. It stores the dequoted string,
 * its length, the length of state information,
 * and the current quoting state within the dequoted string.
 */
struct dequote
{
	char *new;
	size_t length;
	size_t the_state_len;
	quote_state q_state;
};

typedef struct dequote dequote_t;
char *remove_quotes(const char *s);
ssize_t remove_quotes_len(const char *str);

/*char *dequote(const char *str);*/
/*size_t dequote_len(const char *str);*/
#endif /*_MYQUOTE_H_*/
