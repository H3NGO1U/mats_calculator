#include "mat.h"
/*parameters: matrix number*/
/*prints the matrix*/
void print_mat(mat** myMats, int num_of_mat)
{
	int i,j;
	double num;
	for(i = 0; i < SIZE; i++){
		printf("\n");
		for(j = 0; j < SIZE; j++)
		{
			num = (myMats[num_of_mat]->matrix)[i][j];
			if(num == 0) num = 0; /*avoid "negative" 0 printing*/
			printf("%7.2f\t", num);  
		}
	}
	printf("\n");
	
}
/*parameters: matrix number, array of doubles*/
void read_mat(mat** myMats, int num_of_mat, double nums[4][4])
{
	int i,j;
	for(i = 0; i<SIZE; i++)
		for(j = 0; j<SIZE; j++)
			(myMats[num_of_mat]->matrix)[i][j] = nums[i][j];
	print_mat(myMats, num_of_mat);
	
}

/*parametrs: three matrix names*/
/*adds two matrixes and stores result in the third*/
void add_mat(mat **myMats, int mat1,int mat2,int mat3)
{
	int i,j;
	double mat_1[4][4] = {0};
	double mat_2[4][4] = {0};
	
	memcpy(mat_1, *(myMats[mat1]) -> matrix, 16*sizeof(double));
	memcpy(mat_2, *(myMats[mat2]) -> matrix, 16*sizeof(double));
	
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			(myMats[mat3] -> matrix)[i][j] = mat_1[i][j] + mat_2[i][j];
	print_mat(myMats, mat3);
}

/*parametrs: three matrix names*/
/*substracts two matrixes and stores result in the third*/
void sub_mat(mat **myMats, int mat1,int mat2,int mat3)
{
	int i,j;
	double mat_1[4][4] = {0};
	double mat_2[4][4] = {0};
	memcpy(mat_1, *(myMats[mat1]) -> matrix, 16*sizeof(double));
	memcpy(mat_2, *(myMats[mat2]) -> matrix, 16*sizeof(double));
	
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			(myMats[mat3] -> matrix)[i][j] = mat_1[i][j] - mat_2[i][j];
	print_mat(myMats, mat3);
	
}

/*parametrs: three matrix names*/
/*multificates two matrixes and stores result in the third*/
void mul_mat(mat **myMats, int mat1 ,int mat2,int mat3)
{
	int i,j;
	double mat_1[4][4] = {0};
	double mat_2[4][4] = {0};
	
	memcpy(mat_1, *(myMats[mat1]) -> matrix, 16*sizeof(double));
	memcpy(mat_2, *(myMats[mat2]) -> matrix, 16*sizeof(double));
	
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			(myMats[mat3] -> matrix)[i][j] = mul_cell(mat_1, mat_2, i, j);
	print_mat(myMats, mat3);
}

/*parameters: two matrix numbers, a real number*/
/*multificates matrix one in the number and stores result in the second*/
void mul_scalar(mat **myMats, int mat1, double scalar,int mat2)
{
	int i,j;
	double mat_1[4][4] = {0};

	memcpy(mat_1, *(myMats[mat1]) -> matrix, 16*sizeof(double));

	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			(myMats[mat2] -> matrix)[i][j] = mat_1[i][j] * scalar;
	print_mat(myMats, mat2);
}

/*parameters: two matrix numbers*/
/*transposes matrix one and stores result in the second*/

void trans_mat(mat **myMats, int mat1,int mat2)
{
	int i, j;
	double mat_1[4][4] = {0};

	memcpy(mat_1, *(myMats[mat1]) -> matrix, 16*sizeof(double));
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			(myMats[mat2] -> matrix)[i][j] = mat_1[j][i];
	print_mat(myMats, mat2);
	
}

void stop()
{
	printf("\nexit...\n");
	exit(0);

}
/*used for matrix multifiacation*/
double mul_cell(double mat1[4][4], double mat2[4][4], int row, int col)
{
	int i;
	double sum = 0;
	for(i = 0; i < SIZE; i++)
		sum += mat1[row][i] * mat2[i][col];
	return sum;
}