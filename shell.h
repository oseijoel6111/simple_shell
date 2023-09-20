#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} my_list_t;

typedef struct passInfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	my_list_t *env;
	my_list_t *history;
	my_list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int hsh(info_t *, char **);
int findBuiltIn(info_t *);
void findCMD(info_t *);
void forkCMD(info_t *);
int isCMD(info_t *, char *);
char *dupChars(char *, int, int);
char *findPath(info_t *, char *, char *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int csutom_strlen(char *);
int custom_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *custom_strcat(char *, char *);
char *custom_strcpy(char *, char *);
char *custom_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int interactive(info_t *);
int custom_is_delim(char, char *);
int custom_is_isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int custom_myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
ssize_t getInput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int custom_myunsetenv(info_t *);
int populateEnvList(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);
my_list_t *addNode(my_list_t **, const char *, int);
my_list_t *addNodeEnd(my_list_t **, const char *, int);
size_t printList_str(const my_list_t *);
int deleteNodeAtIndex(my_list_t **, unsigned int);
void freeList(my_list_t **);
size_t list_len(const my_list_t *);
char **myListToStrings(my_list_t *);
size_t printList(const my_list_t *);
my_list_t *nodeStartsWith(my_list_t *, char *, char);
ssize_t getNodeIndex(my_list_t *, my_list_t *);
int is_custom_chain(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replaceVars(info_t *);
int replaceString(char **, char *);

#endif
