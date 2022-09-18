#include "text_meths.h"
/*returns the mat index in the array using the name field*/
/*if an suitable mat isn't found, returns UNDEF_MAT*/
int getMat(mat **myMats, char *str)
{
	int i;
	
	for(i = 0; i < NUM_OF_MATS; i++)
		if(!strcmp(myMats[i]->name, str))
				return i;
	return UNDEF_MAT;
}
/*remove space from begging and end*/
/*if find a space in the middle, changes error to ILLEGAL_SPACE*/
/*if doesn't find any character except spaces, changes error to MISS_ARG*/	
/*returns the new string*/
char* remove_spaces(char* str, int *error)
{
	
	int i = 0, k = 0, loc = start, capacity = 100;
	char c;
	char *newStr = malloc(100*sizeof(char)), *temp = NULL;
	if(str != NULL)
	{
		
		while((c = str[i])!='\0')
		{
			if(k==capacity-1)
			{
				temp = enlarge(newStr, &capacity);
				if(temp!=NULL)
					newStr = temp;
				else
				{
				
					printf("\nUndefined Problem");
					free(newStr);
					stop();
				}
			}
			if(loc == start && !isspace(c)) /*stops ignoring spaces*/
				loc = mid;
			if(loc == mid)
			{
				if(isspace(c))  /*a space after a non-space char*/
					loc = end;
				else
				{	
					newStr[k] = c; /*copies char*/
					k++;
				}
			
			}
			if(loc == end && !isspace(c))
			{
				newStr = NULL; /*we have an illegal space*/
				*error = ILLEGAL_SPACE;
				break;
			}
				
			i++;
		}
	
	}
	if(loc == start) /*there wasnt characters except spaces*/
		*error = MISS_ARG;
	else if(newStr!= NULL)
		newStr[k] = '\0'; /*terminate string*/
	
	return newStr;
}

/*recieves a string clean from spaces*/
/*checks if this string is a decimal number*/
/*uses isdigit() function*/
/*returns 1 if it is a number, else 0*/
int isDigit(char *str)
{
	int i  = 0, dot = 0;
	char c;
	if(str == NULL) return 0;
	while((c=str[i])!='\0')
	{
		if(i == 0 && c == '-') /*for negative numbers*/
			i++;
		else
		{
			if((!isdigit(c) && c!='.') || (c=='.' && dot)) /*two dotes in a number or a different not-digit char*/
				return 0;
			if(c=='.') /*one dot was here*/
				dot = 1;
		
			i++;
		}
	}
	
	return 1;
}

/*dinamic allocation*/
char* enlarge(char *ptr, int *capacity)
{

	char* newPtr = NULL;
	*capacity *= 2;
	newPtr = realloc(ptr,*capacity*sizeof(char));
	return newPtr;
}


