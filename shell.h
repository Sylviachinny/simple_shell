#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "cmd.h"
#include "shellenv.h"
#include "handlerror.h"
#include "getline.h"
#include "shelllst.h"
#include "utilities.h"
#include "strtok.h"
#include "shellhelpertype.h"
extern char **environ;

/**
 * struct store_info - store information
 * @interactive: interactive
 * @argc: argument count
 * @argv: argument vector
 * @file: file
 * @fileno: file number
 * @status: status
 * @line: line
 * @line_read: line read
 * @tokens: tokenization
 * @p_pid: parent process id
 * @cwd_s: command mode
 * @execute: execute
 * @error: error
 * @env: environment
 * @path: path
 * @cmd: change mood
 */
struct store_info
{
	int interactive;
	int argc;
	char **argv;
	char *file;
	int fileno;
	int status;
	char *line;
	size_t line_read;
	char **tokens;
	pid_t p_pid;
	char *cwd_s;
	char *execute;
	int error;
	shell_dict_t *env;
	directory_t *path;
	command_t *cmd;
};

store_info_t *init_prmpt(int ac, char **av);
int release_store_infomation(store_info_t *store_info);

#endif /*SHELL_H_*/
