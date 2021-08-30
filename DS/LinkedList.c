#include<stdio.h>
#include<stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node
{
	ElementType element;
	Position next;
};

List MakeEmpty();
int IsEmpty(List L);
int IsLast(Position P, List L);
void Insert(ElementType X, List L, Position P);
void PrintList(List L);
void Delete(ElementType X, List L);
Position Find(ElementType X, List L);
Position FindPrevious (ElementType X, List L);
void DeleteList (List L);

int main (int argc, char *argv[]){
	char command;
	int key1, key2;
	FILE *input;
	Position header;
	Position tmp = NULL;
	if(argc==1){
		printf("No input file\n");
		return 0;
	}
	else
		input = fopen(argv[1], "r");
	header = MakeEmpty();
	while(1){
		command = fgetc(input);
		if(feof(input)) break;
		switch (command){
			case 'i':
				fscanf(input, "%d %d", &key1, &key2);
				if (key2 == -1){
					Insert(key1, header, header);
					break;
				}
				else
					tmp = Find(key2, header);
					if (tmp ==NULL)
						printf("Insertion(%d) Failed : cannot find the location to be inserted\n", key1);
					else
						Insert(key1, header, tmp);
				break;
			case 'd':
				fscanf(input, "%d", &key1);
				tmp = Find(key1, header);
				if (tmp == NULL)
					printf("Deletion failed : element %d is not in the list\n",key1);
				else
					Delete(key1, header);
				break;
			case 'f':
				fscanf(input, "%d", &key1);
				tmp = FindPrevious(key1, header);
				if(IsLast(tmp, header))
					printf("Could not find %d in the list\n",key1);
				else {
						if(tmp->element>0)
							printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
						else
							printf("Key of the previous node of %d is header.\n",key1);
				}
				break;
			case 'p':
				if (IsEmpty(header)==1)
					printf("your list is empty\n");
				else
					PrintList(header);
				break;
			default:
				break;
		}
	}
	DeleteList(header);
	fclose(input);
	return 0;
}

List MakeEmpty()
{
	List L;
	L = (List)malloc(sizeof(struct Node));
	L->element = 0;
	L->next = NULL;
	return L;
}

int IsEmpty(List L)
{
	return L->next == NULL;
}

int IsLast(Position P, List L)
{
	return P->next == NULL;
}

Position Find(ElementType X, List L)
{
	Position P;
	P=L->next;
	while (P!= NULL && P->element !=X)
		P=P->next;
	return P;
}

Position FindPrevious(ElementType X, List L)
{
	Position P;
	P=L;
	while (P->next!=NULL && P->next->element != X)
		P=P->next;
	return P;
}

void Insert(ElementType X, List L , Position P)
{
	Position tmp;
	tmp =malloc(sizeof(struct Node));
	tmp->element = X;
	tmp->next = P->next;
	P->next = tmp;
}

void Delete(ElementType X, List L)
{
	Position P, TmpCell;
	P=FindPrevious(X,L);
	if (!IsLast(P,L))
	{
		TmpCell = P->next;
		P->next = TmpCell->next;
		free(TmpCell);
	}
}

void DeleteList(List L)
{
	Position P, Tmp;
	P = L->next;
	L->next = NULL;
	while(P!=NULL)
	{
		Tmp = P->next;
		free(P);
		P=Tmp;
	}
	free(L);
}

void PrintList(List L)
{
	Position P;
	P = L->next;
	while (P!=NULL)
	{
		printf("key:%d\t",P->element);
		P=P->next;
	}
	printf("\n");
}
