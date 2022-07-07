/**
 * @file err.h
 *
 * @brief standard error formatting
 *
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#ifndef LOCK_ERR
#  define LOCK_ERR ///< lock: standard lock

#  define POINT '^' ///< @brief format field for error pointer
#  define EXTEND '~' ///<  @brief format field for error pointer extend

/// @brief struct for erroing with file info
struct file_info {
	char* filename;
	char* line;
	char* column;
};

/// @brief struct for erroing with error info (used in source)
struct error_info {
	char* line;
	char* ptr;
};

typedef struct file_info FInfo;
typedef struct ferror_info FEInfo;

typedef int (*function) (void);

extern function const header;
extern function const body;

extern char ERROR;

void Err (int, function, function);
void ErrPromise (int, function, function);
#endif
