#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "mat.h"
#define DELIM ",\n"
#define ILLEGAL_COMD "\nUndefined command name\n"
#define MISS_ARG_MSG printf("\nmissing argument\n")
#define MISS_COMMA_MSG printf("\nmissing comma\n")
#define UNDEF_MAT_MSG printf("\nUndefined matrix name")
#define NOT_NUM_MSG printf("\nargument is not a real number")
#define EXTRA_TEXT_MSG printf("\nExtraneous text after the end of command")
#define ILLEGAL_COMMA_MSG printf("\nillegal comma")
typedef enum LOC
{
	start, mid, end
}LOC;

typedef enum ERROR
{
	UNDEF_MAT = -10,
	MISS_ARG,
	MISS_COMMA,
	ILLEGAL_SPACE,
	NOT_NUM
}ERROR;
void read_mat_tok(mat** , char*, int);
void print_mat_tok(mat**, char*,int);
void math_mat_tok(mat**, char*,int,char*);
void mul_scalar_tok(mat**, char*,int);
void trans_mat_tok(mat**, char*,int);
int get_Mat_tok(mat**, char*, int);
int getMat(mat**, char*);
char* remove_spaces(char*,int*);
int isDigit(char*);
char* enlarge(char*, int*);
