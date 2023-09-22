#include "shellbuiltin.h"


/**
 * _cd_error_s - print an error upon failure to change directory
 * @info: shell info
 * @dir: directory
 */
void _cd_error_s(store_info_t *info, char *dir)
{
	char *error = str_concat(NULL, " ", "can't cd to", dir);

	handle_error(*info->argv, info->line_read, error, *info->tokens, NULL);

	info->status = 2;

	free(error);
}


/**
 * _cd_success_s - update the environment upon success
 * @info: shell info
 */
void _cd_success_s(store_info_t *info)
{
	char **tokens = info->tokens;
	char *setenv_tokens[] = {"setenv", NULL, NULL, NULL};

	info->tokens = setenv_tokens;

	setenv_tokens[1] = "OLDPWD";
	setenv_tokens[2] = info->cwd_s;

	_setenv(info);

	free(info->cwd_s);
	info->cwd_s = getcwd(NULL, 0);

	setenv_tokens[1] = "PWD";
	setenv_tokens[2] = info->cwd_s;

	_setenv(info);

	info->tokens = tokens;

	info->status = EXIT_SUCCESS;
}


/**
 * _cd - changes the directory
 * @info: arguments passed
 *
 * Return: int
 */
int _cd(store_info_t *info)
{
	char *dir = NULL, **args = info->tokens + 1;

	info->status = EXIT_SUCCESS;
	if (*args)
	{
		if (!_strcmp(*args, "-"))
		{
			dir = get_value(info->env, "OLDPWD");
			if (!dir)
				dir = info->cwd_s;

			info->status = chdir(dir);
			if (!info->status)
			{
				write(STDOUT_FILENO, dir, _strlen(dir));
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		else
		{
			dir = *args;
			info->status = chdir(dir);
		}
	}
	else
	{
		dir = get_value(info->env, "HOME");
		if (dir)
			info->status = chdir(dir);
	}
	if (info->status != -1)
		_cd_success_s(info);
	else
		_cd_error_s(info, dir);
	return (info->status);
}
