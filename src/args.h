#ifndef __ARGS_H__
#define __ARGS_H__ 1

extern int streq(char *, char *);
extern int in_args(int, char * argv[], char *, int *);

extern char * str_arg(int, char * argv[], char *, int *);

#endif
