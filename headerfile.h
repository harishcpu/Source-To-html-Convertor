#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "colors.h"

#define MAXLINE 200
#define FILESIZE 2000

void Search(char *line, FILE* dest_fp);
int Keyword(char *str);
int Operator(char *str);
int ProgBar(char *, int , useconds_t );

