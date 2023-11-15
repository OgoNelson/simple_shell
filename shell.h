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

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @_num: the number field
 * @_str: a string
 * @_next: points to the next node
 */
typedef struct liststr
{
	int _num;
	char *_str;
	struct liststr *_next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@_path: a string path for the current command
 *@argc: the argument count
 *@linecount: the error count
 *@error_num: the error code for exit()s
 *@linecountflag: if on count this line of input
 *@filename: the program filename
 *@_env: linked list local copy of environ
 *@myenviron: custom modified copy of environ from LL env
 *@myhistory: the history node
 *@myalias: the alias node
 *@envchanged: on if environ was changed
 *@_status: the return status of the last exec'd command
 *@cmdbuf: address of pointer to cmdbuf, on if chaining
 *@cmdbuf_type: CMD_type ||, &&, ;
 *@inputdir: dir from which to read line input
 *@_histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *_path;
	int argc;
	unsigned int linecount;
	int error_num;
	int linecountflag;
	char *filename;
	list_t *_env;
	list_t *myhistory;
	list_t *myalias;
	char **myenviron;
	int envchanged;
	int _status;

	char **cmdbuf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmdbuf_type; /* CMD_type ||, &&, ; */
	int inputdir;
	int _histcount;
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


/* for shloop.c */
int shloop(info_t *, char **);
int findbuiltin(info_t *);
void findcmd(info_t *);
void forkcmd(info_t *);

/* for shellparser.c */
int exec_cmd(info_t *, char *);
char *dupli_chars(char *, int, int);
char *find_cmd(info_t *, char *, char *);

/* for shellerrors.c */
void _putsE(char *);
int _putcharE(char);
int _wputfd(char c, int fd);
int _putstrfd(char *str, int fd);

/* for str.c */
int _mystrlen(char *);
int _mystrcomp(char *, char *);
char *startstr(const char *, const char *);
char *_strconcat(char *, char *);

/* for str1.c */
char *_mystrcpy(char *, char *);
char *_mystrdupli(const char *);
void _putstr(char *);
int _myputchar(char);

/* for shellexits.c */
char *_mystrncpy(char *, char *, int);
char *_strnconcat(char *, char *, int);
char *_mystrchr(char *, char);

/* for mytokenizer.c */
char **strtowrd(char *, char *);
char **strtowrd2(char *, char);

/* for reallocator.c */
char *_mymemset(char *, char, unsigned int);
void freestr(char **);
void *_reallocmem(void *, unsigned int, unsigned int);

/* for freemem.c */
int freeptr(void **);

/* for interactive.c */
int interact(info_t *);
int my_delim(char, char *);
int _alpha(int);
int interactive(char *);

/* for shellerrors1.c */
int _strtoint(char *);
void print_E(info_t *, char *);
int print_deci(int, int);
char *convertnumb(long int, int, int);
void rm_comments(char *);

/* for inbuiltfnc.c */
int _exitshell(info_t *);
int _cdir(info_t *);
int _helper(info_t *);

/* inbuiltinfnc1.c */
int _myhist(info_t *);
int _myshellalias(info_t *);

/*for mygetline.c */
ssize_t getinput(info_t *);
int _mygetline(info_t *, char **, size_t *);
void sigint_Handler(int);

/* for mygetinfo.c */
void clearinfo(info_t *);
void setinfo(info_t *, char **);
void freeinfo(info_t *, int);

/* for myenvironvar.c */
char *_getEnv(info_t *, const char *);
int _myEnv(info_t *);
int _mysetEnv(info_t *);
int _myunsetEnv(info_t *);
int populateEnv_list(info_t *);

/* for mygetenv.c */
char **getEnviron(info_t *);
int _unsetEnv(info_t *, char *);
int _setEnv(info_t *, char *, char *);

/* for historyfile.c */
char *gethistory_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int buildhistory_list(info_t *info, char *buf, int linecount);
int renumber_hist(info_t *info);

/* for mylists.c */
list_t *addnode(list_t **, const char *, int);
list_t *addnode_end(list_t **, const char *, int);
size_t printlist_str(const list_t *);
int delete_node_index(list_t **, unsigned int);
void freelist(list_t **);

/* for mylists1.c */
size_t listlen(const list_t *);
char **list_to_str(list_t *);
size_t printlist(const list_t *);
list_t *node_starts(list_t *, char *, char);
ssize_t getnode_index(list_t *, list_t *);

/* for shellvars.c */
int deli_chain(info_t *, char *, size_t *);
void checkchain(info_t *, char *, size_t *, size_t, size_t);
int replace_myalias(info_t *);
int replace_myvars(info_t *);
int replace_mystring(char **, char *);

#endif
