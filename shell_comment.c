#include "main.h"

/**
 * filter_comment - Remove comments from a command's token list.
 * @cmd_se: Pointer to a command structure containing tokens.
 */
void filter_comment(command_t *cmd_se)
{
	char **tokenize, *temp, **new_cmd;

	for (tokenize = cmd_se->tokens; *tokenize; ++tokenize)
	{
		if (**tokenize == '#')
		{
			temp = *tokenize;
			*tokenize = NULL;
			new_cmd = duplicateStringArray(cmd_se->tokens);
			*tokenize = temp;
			release_mem(&(cmd_se->tokens));
			cmd_se->tokens = new_cmd;
			free_command_lst(&(cmd_se->link));
			return;
		}
	}
}
