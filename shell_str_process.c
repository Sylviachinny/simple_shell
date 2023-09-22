#include "myqoute.h"

/**
 * quote_factory - function pointer string processor helper
 * @state: state
 * Return: state with associated c
 */
quote_state_fp quote_factory(quote_state state)
{
	switch (state)
	{
		case QUOTE_NONE:
			return (quote_none);
		case QUOTE_DOUBLE:
			return (quote_double);
		case QUOTE_SINGLE:
			return (quote_single);
		case QUOTE_ESCAPE:
			return (quote_escape);
		case QUOTE_WORD:
			return (quote_word);
	}
	return (NULL);
}

/**
 * quote_str_len - get the length of state
 * @str: string
 * @state: state
 * Return: length
 */
size_t quote_str_len(const char *str, quote_state state)
{
	return (quote_factory(state)(str, NULL));
}


/**
 * quote_proc - character processor function
 * @c: character to process
 * Return: the state of character base on the processor
 */
quote_state quote_proc(char c)
{
	if (_isspace(c))
		return (QUOTE_NONE);
	else if (c == '"')
		return (QUOTE_DOUBLE);
	else if (c == '\'')
		return (QUOTE_SINGLE);
	else if (c == '\\')
		return (QUOTE_ESCAPE);
	else
		return (QUOTE_WORD);
}

/**
 * remove_quotes_len - Calculate the length of a string with removed quotes.
 * @str: The input string with quotes.
 *
 * This function calculates the length of a string with quotes removed.
 *
 * Return: The length of the string after removing quotes.
 */
ssize_t remove_quotes_len(const char *str)
{
	size_t length = 0, stateLen;
	quote_state state;

	while (*str)
	{
		state = quote_proc(*str);
		str += (1 && (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE)));
		stateLen = quote_str_len(str, state);
		if (state & QUOTE_DOUBLE)
		{
			for ( ; stateLen; --stateLen)
			{
				if (quote_proc(*str++) & QUOTE_ESCAPE)
				{
					if (*str == '\n')
					{
						++str, --stateLen;
						continue;
					}
					if (is_double_quote_escape(*str))
						++str, --stateLen;
				}
				length++;
			}
		}
		length += stateLen;
		str += stateLen;
		str += (*str && (state & (QUOTE_DOUBLE | QUOTE_SINGLE)));
	}
	return (length);
}

/**
 * remove_quotes - Remove quotes from a string.
 * @s: The input string with quotes.
 *
 * This function removes quotes from a given input string and returns a new
 * string without quotes.
 *
 * Return: A dynamically allocated string without quotes, or NULL on failure.
 */
char *remove_quotes(const char *s)
{
	dequote_t quote;

	quote.length = 0;

	if (s == NULL)
		return (NULL);
	quote.new = malloc(sizeof(char) * (remove_quotes_len(s) + 1));
	if (!quote.new)
		return (NULL);
	while (*s)
	{
		quote.q_state = quote_proc(*s);
		s += (1 && (quote.q_state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE)));
		quote.the_state_len = quote_str_len(s, quote.q_state);
		if (quote.q_state & QUOTE_DOUBLE)
		{
			for (; quote.the_state_len; --quote.the_state_len)
			{
				if (quote_proc(*s) & QUOTE_ESCAPE)
				{
					if (*s == '\n')
					{
						++s, --quote.the_state_len;
						continue;
					}
					if (is_double_quote_escape(*s))
						++s, --quote.the_state_len;
				}
				quote.new[quote.length++] = s[-1];
			}
		}
		_memcpy(quote.new + quote.length, s, quote.the_state_len);
		quote.length += quote.the_state_len;
		s += quote.the_state_len;
		s += (*s && (quote.q_state & (QUOTE_DOUBLE | QUOTE_SINGLE)));
	}

	quote.new[quote.length] = '\0';
	return (quote.new);
}
