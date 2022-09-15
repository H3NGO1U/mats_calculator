#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 4
#define NUM_OF_MATS 6
typedef struct mat
{
	double matrix[4][4];
	char *name;
}mat;

void read_mat(mat**, int, double[4][4]);
void print_mat(mat**, int);
void add_mat(mat**, int,int,int);
void sub_mat(mat**, int,int,int);
void mul_mat(mat**, int,int,int);
void mul_scalar(mat**, int,double,int);
void trans_mat(mat**, int,int);
void stop(void);
double mul_cell(double[4][4], double[4][4], int, int);