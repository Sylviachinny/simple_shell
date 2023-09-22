#ifndef _SHELLLST_H_
#define _SHELLLST_H_

#include <stdlib.h>
#include "utilities.h"
#include "shellhelpertype.h"

/**
 * struct directory - Represents a node in a linked list of directories.
 * @path: The path of the directory.
 * @link: A pointer to the next directory in the linked list.
 *
 * Description: This structure is used to represent a node in a linked
 * list of directories. It contains the path of the directory and
 * a pointer to the next directory in the list.
 * This is often used to create a linked list of directories in a
 * file system or directory traversal operation.
 */
struct directory
{
	char *path;
	struct directory *link;
};

directory_t *path_wrapper(const char *path, char delim);
directory_t *path_to_list(directory_t **tail_ptr, const char *path,
		char delim);
directory_t *add_at_beg(directory_t **headptr, const char *path);
directory_t *dir_at_the_end(directory_t **dir_head, const char *path);
void free_dir(directory_t **head_ptr);

#endif /*_SHELLLST_H_*/
