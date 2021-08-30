#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* S, int X);
int Pop(Stack* S);
int Top(Stack* S);
void DeleteStack(Stack* S);
int IsEmpty(Stack *S);
int IsFull(Stack *S);
int Postfix(Stack* S, char input_str);

void main(int argc, char* argv[]){
	FILE* fi =fopen(argv[1], "r");
	Stack* stack;
	char input_str[101];
	int max, i, result;
	fgets(input_str, 101, fi);
	stack = CreateStack(10);
	
	printf("Top numbers :");
	for(i=0; i<strlen(input_str) && input_str[i]!='#'; i++)
	{
		result = Postfix(stack, input_str[i]);
	}

	printf("\nevalutation result : %d\n", result);
	fclose(fi);
	DeleteStack(stack);
}

Stack* CreateStack(int max){
	Stack* S;
	S=malloc(sizeof(struct Stack));
	S->key=malloc(sizeof(int)*max);
	S->max_stack_size = max;
	S->top = -1;
	return S;
}

void Push(Stack* S, int X){
	if(IsFull(S))
	{	printf("Full stack\n");
		exit(0);
	}
	else
		S->key[++S->top]=X;
}

int Pop(Stack* S){
	if(IsEmpty(S))
	{	printf("Empty stack\n");
		exit(0);
	}
	else
		return S->key[S->top--];
}

int Top(Stack* S){
	if(!IsEmpty(S))
		return S->key[S->top];
	else
		printf("Empty stack\n");
	return 0;
}

void DeleteStack(Stack* S){
	free(S->key);
	free(S);
}

int IsEmpty(Stack *S){
	if(S->top<0)
		return 1;
	return 0;
}
int IsFull(Stack *S){
	if(S->top>=9)
		return 1;
	return 0;
}
int Postfix(Stack* S, char input_str){
	int num1,num2,result;
	switch(input_str)
	{
		case'+':
			num1=Pop(S);
			num2=Pop(S);
			result=num1+num2;
			Push(S,result);
			printf("%d ",Top(S));
			return result;
		
		case'-':
			num1=Pop(S);
			num2=Pop(S);
			result=num2-num1;
			Push(S,result);
			printf("%d ",Top(S));
			return result;
			
		case'*':
			num1=Pop(S);
			num2=Pop(S);
			result=num1*num2;
			Push(S,result);
			printf("%d ",Top(S));
			return result;

		case'/':
			num1=Pop(S);
			num2=Pop(S);
			result=num2/num1;
			Push(S,result);
			printf("%d ",Top(S));
			return result;
		
		case'%':
			num1=Pop(S);
			num2=Pop(S);
			result=num2%num1;
			Push(S,result);
			printf("%d ",Top(S));
			return result;

		default:	//integer
			Push(S,input_str-'0');
			printf("%d ",Top(S));
			return input_str;
	}
}
