#include "shellbuiltin.h"

/**
 * my_atoi - Convert a string to an unsigned integer.
 * @str: The input string to convert.
 *
 * Return: Returns the converted unsigned integer value from the string.
 * If the string contains non-numeric characters or the value exceeds UINT_MAX,
 * it returns UINT_MAX.
 */
unsigned int my_atoi(char *str)
{
	atoi_t atou;

	atou.num = 0;
	size_t len = _strlen(str);

	for (atou.iterator = 0; atou.iterator < len; atou.iterator++)
	{
		if (UINT_MAX / 10 < atou.num)
			return (UINT_MAX);
		atou.num *= 10;
		atou.curr_digit = str[atou.iterator] - '0';
		if (UINT_MAX - atou.curr_digit < atou.num)
			return (UINT_MAX);
		atou.num += atou.curr_digit;
	}

	return (atou.num);
}

/**
 * free_all - frees all memory
 * @n: number of arguments
 * Return: void
 */
void free_all(const unsigned int n, ...)
{
	va_list args;
	unsigned int i;
	char *ptr;

	va_start(args, n);
	for (i = 0; i < n; i++)
	{
		ptr = va_arg(args, char *);
		free(ptr);
	}
	va_end(args);
}


/**
 * duplicateStringArray - Duplicate a string array.
 *
 * @array: The original string array to duplicate.
 *
 * Return: A new dynamically allocated array containing duplicated strings, or
 *         NULL on failure.
 */
char **duplicateStringArray(char **array)
{
	char **arr_dup = NULL;
	size_t length = 0, iterator;

	if (!array || !*array)
		return (NULL);
	while (array[length++])
		;
	arr_dup = malloc(sizeof(*arr_dup) * length);
	if (arr_dup == NULL)
		return (NULL);
	length = 0;
	while (array[length])
	{
		arr_dup[length] = _strdup(array[length]);
		if (arr_dup[length] == NULL)
		{
			for (iterator = 0; iterator < length; iterator++)
			{
				free_all(1, arr_dup[iterator]);
			}
			free_all(1, arr_dup);
			return (NULL);
		}
		length++;
	}
	return (arr_dup);
}
