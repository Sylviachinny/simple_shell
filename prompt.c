#include "main.h"

/**
 * command_processor - Process and tokenize commands from user input.
 * @shell_info: Pointer to the store_info_t structure containing shell
 * information.
 *
 * Return: The total number of valid commands processed from the user input.
 */
int command_processor(store_info_t *shell_info)
{
	char **tokenize, *token;
	size_t count = 0;
	command_t *command = shell_info->cmd = _update_the_cmd(shell_info->line);

	while (command)
	{
		filter_comment(command);
		if (!command->tokens)
		{
			command = command->link;
			del_cmd_at_pos(&(shell_info->cmd), count);
			continue;
		}
		process_aliases(shell_info->aliases, &(command->tokens));
		if (!command->tokens)
		{
			command = command->link;
			del_cmd_at_pos(&(shell_info->cmd), count);
			continue;
		}
		tokenize = command->tokens;
		for (token = *tokenize; token; token = *(++tokenize))
		{
			*tokenize = remove_quotes(token);
			free_all(1, token);
		}
		command = command->link;
		++count;
	}

	return (count);
}

/**
 * _sigint - reprompts
 * @signal: signal passed
 */
void _sigint(int signal __attribute__((unused)))
{
	fflush(STDIN_FILENO);
	write(STDERR_FILENO, "\nshell$ ", 8);
}

/**
 * main - The entry point of the shell program.
 * @ac: The number of command-line arguments.
 * @av: An array of command-line argument strings.
 *
 * This function initializes the shell, sets up signal handling,
 * and enters the main shell loop. It reads user input, processes
 * and tokenizes shell commands, executes them, and releases resources.
 *
 * Return: The exit status code of the shell.
 */
int main(int ac, char **av)
{
	store_info_t *shell_info;

	shell_info = init_prmpt(ac, av);
	signal(2, _sigint);

	while (read_usr_input(shell_info))
	{
		command_processor(shell_info);
		while ((shell_info->tokens = remove_cmd(&(shell_info->cmd))))
		{
			executeShellCommand(shell_info);
			release_mem(&(shell_info->tokens));
		}
		free_all(1, shell_info->line);
		shell_info->line = NULL;
	}
	if (shell_info->interactive)
		write(STDOUT_FILENO, "\n", 1);

	if (shell_info->file)
		close(shell_info->fileno);

	exit(release_store_infomation(shell_info));
}
