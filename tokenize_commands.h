#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "text_meths.h"
void read_mat_tok(mat** , char*, int);
void print_mat_tok(mat**, char*,int);
void math_mat_tok(mat**, char*,int,char*);
void mul_scalar_tok(mat**, char*,int);
void trans_mat_tok(mat**, char*,int);
int get_Mat_tok(mat**, char*, int);