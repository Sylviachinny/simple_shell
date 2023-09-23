#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>

#include "shellbuiltin.h"
#include "cmd.h"
#include "dictionary.h"
#include "shellenv.h"
#include "handlerror.h"
#include "shell.h"
#include "shelllst.h"
#include "shellpath.h"
#include "myqoute.h"
#include "utilities.h"
#include "strtok.h"
#include "shellhelpertype.h"

extern char **environ;

bool read_usr_input(store_info_t *input_info);
quote_state process_usr_input(char **line_input, int fd);


/*******COMMAND EXECUTION FUNCTION*******/
int exec_init(store_info_t *shell_info);
int executeShellCommand(store_info_t *shell_info);
int command_processor(store_info_t *shell_info);
void _sigint(int signal __attribute__((unused)));

/*********REMOVE COMMENT FUNCTION*********/
void filter_comment(command_t *cmd_se);
#endif /*MAIN_H*/
