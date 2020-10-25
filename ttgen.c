#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct data
{
    int value;
    struct data * next;
} Data;
 
typedef Data * DataList;

typedef int (*CallBack)(DataList);
int * decToBinary(int n) 
{ 
    int * binaryNum = calloc(14, sizeof(int)); 
  
    int i = 0; 
    while (n > 0) { 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
    return binaryNum;
}

Data * createData(int value)
{
    Data * dataptr;
    dataptr = malloc(sizeof(Data));
    dataptr -> value = value;
    dataptr -> next = NULL;
    return dataptr;
}

void appendData(DataList *lstptr, Data * newptr)
{
	if (*lstptr == NULL)
	{
		*lstptr = newptr;
		return;
	}
	appendData(&((*lstptr)->next), newptr);
	return;
}


int main(){
    int vars, vars2, i, j, fr;
    char * str = malloc(sizeof(char)*24);
    char * cut = malloc(sizeof(char)*32);
    char * str2 = malloc(sizeof(char)*24);
    DataList bit_list = NULL;
    int * temp = malloc (sizeof(int) * vars);
    printf("<<Welcome to the Testbench Template Generator (TTGen) by th_valb7>>\n==============================================\n");
    printf(">>Please insert the name of this CUT: ");
    scanf("%s", cut);  
    printf(">>Please insert the format of the inputs (i.e. 'In' or 'in' for In* and in* respectively): ");
    scanf("%s", str);  
    printf(">>Please insert the format of the outputs (i.e. 'Out' or 'out' for Out* and out* respectively): ");
    scanf("%s", str2);  
    printf(">>Please insert the number of inputs: ");
    scanf("%d", &vars);  
    printf(">>Please insert the number of outputs: ");
    scanf("%d", &vars2);  
    printf(">>Please insert the step (pulse length): ");
    scanf("%d", &fr);  

    printf("\ntestbench.v TEMPLATE:\n\nmodule //NAME_OF_MODULE;\n\nreg ");
    for (i=0;i<vars;i++)
    {
        printf("%s%c", str, (65 + i));
        if (i != vars - 1) {
            printf(", ");
        } 
        
    }
    printf(";\nwire ");
    for (i=0;i<vars2;i++)
    {
        printf("%s%c", str2, (65 + vars + i));
        if (i != vars2 - 1) {
            printf(", ");
        } 
        
    }
    printf(";\n\n//OTHER_MODULE_NAME %s (", cut);
    for (i=0;i<vars;i++)
    {
        printf("%s%c, ", str, (65 + i));
        
    }
    for (i=0;i<vars2;i++)
    {
        printf("%s%c", str2, (65 + vars + i));
        if (i != vars2 - 1) {
            printf(", ");
        } 
        
    }
    printf(");\n\ninitial\n begin\n");
	for(i=0;i<pow(2, vars);i++)
	{
		temp = decToBinary (i);
        if (i!=0)
        {
            printf("#%d\t", fr);
        }
        else printf("\t");
		printf("\t%sA=%d;\t", str, temp[vars-1]);
		bit_list = createData (temp[vars-1]);
		for (j=vars-2; j>=0; j--)
		{
			printf("%s%c=%d;\t", str, (64 + vars - j), temp[j]);
			appendData (&bit_list, createData(temp[j]));
		}
    
		printf("\n");
		
	}
    printf("#%d\t$stop;\n end\n\n", fr);
    printf("initial $monitor ($time , , \"");
    for (i=0;i<vars;i++)
    {
        printf("%s%c=%%b, ", str, (65 + i));
        
    }
    for (i=0;i<vars2;i++)
    {
        printf("%s%c=%%b", str2, (65 + vars + i));
        if (i != vars2 - 1) {
            printf(", ");
        } 
        
    }
    printf("\", ");
    for (i=0;i<vars;i++)
    {
        printf("%s%c, ", str, (65 + i));
        
    }
    for (i=0;i<vars2;i++)
    {
        printf("%s%c", str2, (65 + vars + i));
        if (i != vars2 - 1) {
            printf(", ");
        } 
        
    }
    printf(");\n\nendmodule\n\nCopy and paste to your Notepad++ or default Modelsim notepad.\n");
    system("pause");
    return 0;

}