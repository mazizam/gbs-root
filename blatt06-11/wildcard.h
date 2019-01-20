#include<stdlib.h>
#include<stdio.h>
#include "list.h"
#include<string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
list_t* parser(char* ,char** );

list_t* wildcard(char* ,char** );
