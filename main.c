#include "text_meths.h"

mat* create_mat(const char*);
void readCommand(mat**);
void printInput(char*);
void freeMat(mat**);
int main()
{
	mat *myMats[NUM_OF_MATS];
	myMats[0] = create_mat("MAT_A");
	myMats[1] = create_mat("MAT_B");
	myMats[2] = create_mat("MAT_C");
	myMats[3] = create_mat("MAT_D");
	myMats[4] = create_mat("MAT_E");
	myMats[5] = create_mat("MAT_F");
	
	while(1)
		readCommand(myMats);
	freeMat(myMats); /*free the memory allocated to the mat*/
	return 1;  
	
}
/*create new mat with a matrix initalized with zeroes and name*/
/*returns a pointer to the mat*/
mat* create_mat(const char* name)
{
	int i,j;
	mat *newMat= NULL;
	newMat = (mat *)malloc(sizeof(mat));
	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			newMat->matrix[i][j] = 0;
	newMat->name = malloc(sizeof(char)*6);
	strcpy(newMat->name,name);
	return newMat;
	
}
/*reads the command into a dinamic buffer, interpretates the command-name and sends to the appropriate function*/
void readCommand(mat** myMats)
{
	char c;
	int capacity = 100;
	int i = 0,j, spaces, loc = start,  endOfLine = 0, foundComma, legal_end = 1, size_of_buff;
	    char *Buff = malloc(100*sizeof(char)), *temp; /*temp for increasing Buff*/
	char *command;
	printf("\nEnter Your Command\n");
	
	
	while(!endOfLine && (c=getchar())!=EOF)
	{
		if(i == capacity -1) /*allocate more space*/
		{
			temp = enlarge(Buff, &capacity);
			if(temp!=NULL)
				Buff = temp;
			else
			{
				
				printf("\nUndefined Problem");
				free(Buff);
				stop();
			}
			
		}
		/*end of command is '\n' after a non empty line*/
		if(c == '\n'&&loc==mid)
			endOfLine = 1; /*end of command-line*/
			
		
		if(loc == start && !isspace(c))
			loc = mid; /*if we get enter in mid stage, it would be the end of command*/ 
			
		
		Buff[i] = c;
		i++;
			
	} /*end of while*/

	Buff[i] = '\0'; /*terminate*/
	size_of_buff = i; /*remembers size of command for future use*/
	
	if(c == EOF)
	{
		printf("\nEOF exception");
		free(Buff);
		stop();
	}

	printInput(Buff);
	
	spaces = 0;
	while(isspace(Buff[spaces]))  /*skip spaces*/
		spaces++;

	command = strtok(Buff+spaces, " \n\t\v\r\f"); /*terminate command*/
	i = 0;
	/*check the command itself for commas, no comma is allowed*/
	while((c=command[i])!='\0')
	{  
		if(c == ',')
		{
			ILLEGAL_COMMA_MSG;
			return;
		}
		i++;
	}
	i++;
	j = i+spaces; /*points to the first arg after the command*/
	foundComma = 0;
	/*check the whole line for illegal commas*/
	loc = start;
	
	while(j<size_of_buff)
	{
		if(Buff[j] == ',')
		{
			if(loc == start)
			{	
				ILLEGAL_COMMA_MSG;
				return;
			}
			if(!foundComma)
				foundComma = 1;
			else 
			{
				printf("\nillegal consecutive commas");
				return;
			}
			
		}
		else if(!isspace(Buff[j]))
		{
			loc = mid;
			foundComma = 0;
		}
		j++;
	}
	
	/*last arg is comma, can be "missing arg" or "extra text" errors*/
	if(foundComma)
		legal_end = 0;

	j = i +spaces;
	
	while(j<size_of_buff && isspace(Buff[j]))  /*skip spaces in the begging of the remaining command*/
		j++;
	
	/*decide on the appropriate command function*/
	if(!strcmp(command, "stop"))
	{
			free(Buff);
			
			if(j<size_of_buff)
				EXTRA_TEXT_MSG;
			
			else stop();
			return;
	}
	if(!strcmp(command, "read_mat"))
	
				
			read_mat_tok(myMats, Buff+j, legal_end);
	
	else if(!strcmp(command, "print_mat"))
	
			print_mat_tok(myMats, Buff+j, legal_end);
	
	
	else if(!strcmp(command, "add_mat")||
		!strcmp(command, "sub_mat")||
		!strcmp(command, "mul_mat"))
	
		math_mat_tok(myMats, Buff+j, legal_end, command);
	

	else if(!strcmp(command, "mul_scalar"))
		mul_scalar_tok(myMats, Buff+j, legal_end);
	else if(!strcmp(command, "trans_mat"))
		trans_mat_tok(myMats, Buff+j, legal_end);
	else printf(ILLEGAL_COMD);
	free(Buff);
	
}
/*prints the input*/
void printInput(char *input)
{
	int c, i = 0;
	printf("\n");
	while((c=input[i])!='\0')
	{
		printf("%c", c);
		i++;
	}
}

/*free the memory allocation*/
void freeMat(mat **myMats)
{
	int i;
	for(i = 0; i < NUM_OF_MATS; i++)
	{
		free(myMats[i]->name);
		myMats[i]->name = NULL;
		free(myMats[i]);
		myMats[i] = NULL;
		
	}
}


