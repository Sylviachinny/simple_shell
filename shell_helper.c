#include "main.h"
#include "getline.h"

/**
 * read_usr_input - Read user input and process it
 * @input_info: A pointer to a structure containing information about the input.
 * 
 * Return: A dynamically allocated string containing the user's input,
 * or NULL if there was an error or if the user entered no input
*/
bool read_usr_input(store_info_t *input_info)
{
    char *temp = NULL, *line = NULL;
    if (input_info->interactive)
        write(STDIN_FILENO, "shell$ ", 7);
    input_info->line_read += 1;

    while(process_usr_input(&input_info->line, input_info->fileno) & (QUOTE_DOUBLE |
			    QUOTE_SINGLE | QUOTE_ESCAPE))
    {
        temp = line;
        line = str_concat(NULL, "", temp, input_info->line);
        free_all(2, temp, input_info->line);
        if (input_info->interactive)
            write(STDIN_FILENO, "> ", 2);
        input_info->line_read += 1;
    }

    if (line)
    {
        temp = input_info->line;
        input_info->line = str_concat(NULL, "", line, temp);
        free_all(2, temp, line);
    }
    return (input_info->line);
}

/**
 * process_usr_input - Process user input
 * @line_input: line input parameter
 * @fd: file descriptor
 * Return: state
*/
quote_state process_usr_input(char **line_input, int fd)
{
   char *line = *line_input = my_getline(fd);
   static quote_state state = QUOTE_NONE; /*maintain state accross function calls*/
   size_t index = 0;

   if (line)
   {
      switch (state & (QUOTE_DOUBLE | QUOTE_SINGLE))
      {
         case QUOTE_DOUBLE:
         case QUOTE_SINGLE:
               do
               {
                  index += quote_str_len(line + index, state);
                  if (line[index] == '\0')
                     continue;
                  if (state & (QUOTE_DOUBLE | QUOTE_SINGLE))
                     index += 1;
                    /*Fall-through*/
         case 0:
		            state = quote_proc(line[index]);
		            if (state & (QUOTE_DOUBLE | QUOTE_SINGLE | QUOTE_ESCAPE))
			            index += 1;
               } while (line[index]);
      }
   }
   return (state);
}

/**
 * exec_init - Execute a shell command in a child process.
 * @shell_info: Pointer to the shell information struct.
 *
 * This function forks a child process to execute a shell command and waits for
 * the child process to complete. It handles errors and cleanup.
 *
 * Return: The exit status of the child process.
 */
int exec_init(store_info_t *shell_info)
{
    char *exe, **argv, **env;

	switch (fork())
	{
	case 0:
		exe = shell_info->execute;
		argv = shell_info->tokens;
		env = build_env_array(shell_info->env);

		shell_info->execute = NULL;
		shell_info->tokens = NULL;
		release_store_infomation(shell_info);

		execve(exe, argv, env);
		perror(*argv);

		if (shell_info->file)
			close(shell_info->fileno);

		free(exe);
		release_mem(&argv);
		release_mem(&env);
		exit(EXIT_FAILURE);
		break;
	case -1:
		handle_error(*shell_info->argv, shell_info->line_read, "Cannot fork", NULL);
		shell_info->status = 2;
		break;
	default:
		wait(&shell_info->status);
		shell_info->status = WEXITSTATUS(shell_info->status);
		break;
	}
	free(shell_info->execute);
	shell_info->execute = NULL;
    return (shell_info->status);
}

/**
 * executeShellCommand - Execute a shell command.
 * @shell_info: Pointer to the shell information struct.
 *
 * This function checks if the command is a built-in shell command and executes
 * it if it is. If not, it attempts to execute an external command, handling
 * errors and permissions. It returns the exit status of the command execution.
 *
 * Return: The exit status of the executed command.
 */
int executeShellCommand(store_info_t *shell_info)
{
    const builtin_t *builtin = get_builtin(*shell_info->tokens);

    if(builtin)
       return (builtin->built_f(shell_info));
    if (_strchr(*shell_info->tokens, '/') == -1)
    {
        free_dir(&shell_info->path);
        shell_info->path = path_wrapper(get_value(shell_info->env, "PATH"), ':');
        shell_info->execute = handle_path(shell_info, shell_info->path);
    }
    else
        shell_info->execute = _strdup(*shell_info->tokens);
    if (shell_info->execute && access(shell_info->execute, X_OK) == 0)
        return (exec_init(shell_info));
    if (shell_info->execute)
    {
        handle_error(*shell_info->argv, shell_info->line_read, "Permissioned denied",
        *shell_info->tokens, NULL);
        shell_info->status = 126;
    }
    else
    {
        handle_error(*shell_info->argv, shell_info->line_read, "Not found",
        *shell_info->tokens, NULL);
        shell_info->status = 127;
    }

    return (shell_info->status);      
}