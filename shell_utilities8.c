#include "myqoute.h"

/**
 * _isalnum - checks if the character is alphanumeric
 * @c: character to check
 * Return: If c is alphanumeric, return 1. Otherwise, return 0.
 */
bool _isalnum(int c)
{
	return (_isalpha(c) || _isdigit(c));
}

/**
 * _isalpha - checks if the character is alphabetic
 * @c: character to check
 * Return: If c is alphabetic, return 1. Otherwise, return 0.
 */
bool _isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/**
 * _isdigit - checks if the character is digit
 * @c: character to check
 * Return: int
 */
bool _isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
