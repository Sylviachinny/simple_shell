#include "main.h"
/**
 * cd_command - change directory
 * @av: argument vector
 * @count: the number of elements in the av array
 * Return: 0 on success, -1 on failure
 */
int cd_command(char **av, int count)
{
	char hyphen[] = "-", *hsh = "./prompt";
	char *buff = malloc(sizeof(char) * 1024);

	if (av[1] == NULL)
	{
		if (!_getenv("HOME"))
			printerror(&hsh, count, av);
		else
		{
			chdir(_getenv("HOME"));
			setenv("OLDPWD", _getenv("PWD"), 1);
			setenv("PWD", getcwd(buff, sizeof(char) * 1024), 1);
		}
	}
	else if (_strcmp(av[1], hyphen) == 0)
	{
		if (!_getenv("OLDPWD"))
			setenv("OLDPWD", _getenv("PWD"), 1);
		else
		{
			chdir(_getenv("OLDPWD"));
			setenv("OLDPWD", _getenv("PWD"), 1);
			setenv("PWD", getcwd(buff, sizeof(char) * 1024), 1);
		}
		write(1, _getenv("PWD"), _strlen(_getenv("PWD")));
		write(1, "\n", 1);
	}
	else if (av[1] != NULL && av[1] != hyphen)
	{
		if (access(av[1], F_OK) == -1)
			printerror(&hsh, count, av);
		else
		{
			setenv("OLDPWD", _getenv("PWD"), 1);
			chdir(av[1]);
			setenv("PWD", getcwd(buff, sizeof(char) * 1024), 1);
		}
	}
	free(buff);
	return (0);
}

/**
 * cmd_helper - helper function for cd
 * @current_direc: current directory
 * @dir: directory
 *
 * Return: 0 on success, -1 on failure
 */
int cmd_helper(char *current_direc, const char *dir __attribute__((unused)))
{
	if (_setenv("OLDPWD", current_direc) != 0)
	{
		perror("_setenv");
		return (-1);
	}
	return (0);
}

/**
 * change_direc - changes the directory
 * @dir: directory
 * Return: 0 on success, -1 on failure
 */
int change_direc(const char *dir)
{
	if (chdir(dir) != 0)
	{
		return (-1);
	}
	return (0);
}

/**
 * get_working_dir - gets the working directory
 * @dir: directory
 *
 * Return: 0 on success, -1 on failure
 */
int get_working_dir(const char *dir __attribute__((unused)))
{
	char new_pwd[DIR_SIZE];

	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}
	else if (_setenv("PWD", new_pwd) != 0)
	{
		perror("_setenv");
		return (-1);
	}
	return (0);
}
