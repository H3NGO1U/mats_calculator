#include "tokenize_commands.h"
/*uses the getMat function and returns the index of matrix in the array*/
/*also this function prints the neccecery error messages*/
int get_Mat_tok(mat **myMats, char *token, int last)
{
	int error = 0;
	int mat;
	
	char *arg;
	
	arg = remove_spaces(token,&error);
	if(error)
	{
		if(error == MISS_ARG)	
			MISS_ARG_MSG;
		else if(!last) /*illegal space*/
			MISS_COMMA_MSG;	
		else EXTRA_TEXT_MSG;
		free(arg);
		return -1;
	}
	
	mat = getMat(myMats, arg);

	if(mat == UNDEF_MAT)
	{
		UNDEF_MAT_MSG;
		free(arg);
		return -1;
	}
	free(arg);
	return mat;
}	
/*reads from command the matrix name and a list of doubles*/
/*errors when input isn't legal, otherwise calls read_mat*/
void read_mat_tok(mat **myMats, char *input, int legal_end)

{
	char *token = NULL, *arg;
	
	double nums[4][4] = {0};
	int mat, i,j, error;
	
	token = strtok(input, DELIM);
	
	mat = get_Mat_tok(myMats,token, 0);
	if(mat == -1)
		return; 
	token = strtok(NULL, DELIM);
	error = 0;
	i = 0;
	j = 0;

	while(token!=NULL)
	{

		arg = remove_spaces(token,&error);
		if(error == ILLEGAL_SPACE) /*space inside an argument*/
		{
			MISS_COMMA_MSG;
			free(arg);	
			return;
		}
		/*end of commnad*/
		if(error == MISS_ARG) 
		{
			
			if((i+j)>0) /*we read at least one number*/
				break;
			else
			{
				MISS_ARG_MSG;
				free(arg);
				return;
			}
		}
		
		if((i+j)<7)
		{	
			if(isDigit(arg))
					nums[i][j] = atof(arg); /*read the number if it is in the first 16 numbers*/
			j++;
			if(j == 4) /*incrementation*/
			{
				i++;
				if(i < 4)
					j = 0;
			}
		}
		if(!isDigit(arg)) /*argument in the list is not a number*/
		{
			
				NOT_NUM_MSG;
				free(arg);
				return;

		}
		free(arg); /*free before next iteration*/
		token = strtok(NULL, DELIM);	/*read next argument*/
		
	}
	if(!(i+j))  /*if we dont have any numbers in the list */
		MISS_ARG_MSG;
	
	else if(!legal_end)
		EXTRA_TEXT_MSG; /*if we DONT miss args, but have illegal comma at the end*/
	else
		read_mat(myMats, mat,nums);
	
}

/*reads a matrix name to print*/
void print_mat_tok(mat **myMats, char *input, int legal_end)
{
	char *token = strtok(input, DELIM);
	char *arg;
	int error = 0, mat;
	arg = remove_spaces(token,&error);
	
	if(error == MISS_ARG) /*missing matrix name*/
	{	
		MISS_ARG_MSG;
		free(arg);
		return;
	}
	if(error == ILLEGAL_SPACE || !legal_end) /*after we read a matrix name: illegal space means there are more args and we dont need any*/

	{
		EXTRA_TEXT_MSG;	
		free(arg);
		return;
	}
	
	mat = getMat(myMats, arg); /*what mat is it*/
	
	if(mat == UNDEF_MAT)
		UNDEF_MAT_MSG;
		
	else
	{
		token = strtok(NULL, DELIM);
		arg = remove_spaces(token , &error);
		if(error != MISS_ARG) /*we have another arg*/
			EXTRA_TEXT_MSG;
		else  print_mat(myMats, mat);
	}
	free(arg);
	
}

/*this function serves the functions that recieve 3 mats as args*/
/*add_mat, sub_mat, mul_mat*/
void math_mat_tok(mat **myMats, char *input, int legal_end, char *command)
{
	char *token, *arg;
	int mat1, mat2, mat3;
	int error = 0;

	token = strtok(input, DELIM);
	mat1 = get_Mat_tok(myMats, token, 0);
	if(mat1 == -1)
		return;
	
	token = strtok(NULL, DELIM);
	mat2 = get_Mat_tok(myMats, token, 0);
	if(mat2 == -1)
		return;
	
	token = strtok(NULL, DELIM);
	mat3 = get_Mat_tok(myMats, token, 1);
	if(mat3 == -1)
		return;
	if(!legal_end)
	{
		EXTRA_TEXT_MSG;
		return;
	}
	token = strtok(NULL, DELIM);
	arg = remove_spaces(token , &error);
	if(error != MISS_ARG) /*we have another arg*/
		EXTRA_TEXT_MSG;
	else
	{
	/*choose the appropriate function*/
	if(!strcmp(command, "add_mat"))
		add_mat(myMats, mat1, mat2, mat3);
	else if(!strcmp(command, "sub_mat"))
		sub_mat(myMats, mat1, mat2, mat3);
	else 
		mul_mat(myMats, mat1, mat2, mat3);
	}
	free(arg);
	
}
/*for mul_scalar function*/
/*looks for matrix name, then a number, then another matrix name*/
void mul_scalar_tok(mat **myMats, char *input, int legal_end)
{
	char *token, *arg;
	int mat1, mat2;
	int error = 0;
	double scalar;
	token = strtok(input, DELIM);
	mat1 = get_Mat_tok(myMats, token, 0);
	if(mat1 == -1)
		return;
	token = strtok(NULL, DELIM);
	arg = remove_spaces(token,&error);
	if(error)
	{
		if(error == ILLEGAL_SPACE)
			MISS_COMMA_MSG;
			
		
		else MISS_ARG_MSG;
		free(arg);	
		return;
	}
	if(isDigit(arg))
		scalar = atof(arg);
	else 
	{
		NOT_NUM_MSG;
		free(arg);
		return;
	}
	free(arg);
	
	token = strtok(NULL, DELIM);
	mat2 = get_Mat_tok(myMats, token, 1);
	if(mat2 == -1)
		return;
	
	if(!legal_end)
	{
		EXTRA_TEXT_MSG;
		return;
	}	

	token = strtok(NULL, DELIM);
	arg = remove_spaces(token , &error);
	if(error != MISS_ARG)
		EXTRA_TEXT_MSG;
	else 
		mul_scalar(myMats, mat1, scalar, mat2);
	free(arg);
	
}
/*reads input for trans_mat function*/
void trans_mat_tok(mat **myMats, char *input, int legal_end)
{
	char *token, *arg;
	int mat1, mat2;
	int error = 0;
	token = strtok(input, DELIM);
	mat1 = get_Mat_tok(myMats, token, 0);
	if(mat1 == -1)
		return;
	
	token = strtok(NULL, DELIM);
	mat2 = get_Mat_tok(myMats, token, 1);
	if(mat2 == -1)
		return;
	if(!legal_end)
	{
		EXTRA_TEXT_MSG;
		return;
	}

	token = strtok(NULL, DELIM);
	arg = remove_spaces(token , &error);
	if(error != MISS_ARG)
		EXTRA_TEXT_MSG;
	else 
		trans_mat(myMats, mat1, mat2);
	free(arg);
}

