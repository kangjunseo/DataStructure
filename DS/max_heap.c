#include<stdio.h>
#include<stdlib.h>

typedef struct HeapStruct* Heap;
struct HeapStruct{
	int Capacity;
	int Size;
	int *Element;
};

Heap CreateHeap(int heapSize);
void Insert(Heap heap, int value);
int Find(Heap heap, int value);
int DeleteMax(Heap heap);
void PrintHeap(Heap heap);

void main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	Heap maxHeap;
	int heapSize, key;
	while(!feof(fi))
	{
		fscanf(fi,"%c",&cv);
		switch(cv){
		case 'n' :
			fscanf(fi,"%d",&heapSize);
			maxHeap=CreateHeap(heapSize);
			break;
		case 'i' :
			fscanf(fi,"%d",&key);
			Insert(maxHeap,key);
			break;
		case 'd' :
			DeleteMax(maxHeap);
			break;
		case 'p' :
			PrintHeap(maxHeap);
			break;
		case 'f' :
			fscanf(fi,"%d",&key);
			if(Find(maxHeap,key))
				printf("%d is in the heap.\n",key);
			else 
				printf("%d is not in the heap.\n",key);
			break;
		}
	}
}

Heap CreateHeap(int heapSize)
{
	Heap H = malloc(sizeof(struct HeapStruct*));
	H->Capacity=heapSize;
	H->Size=0;
	H->Element=malloc(sizeof(int*)*(heapSize+1));
	return H;
}

void Insert(Heap heap, int value)
{
	int i;
	if (heap->Size>=heap->Capacity)
	{
		printf("Insertion Error: Max Heap is full.\n");
		return;
	}

	if (Find(heap,value))
	{
		printf("%d is already in the heap\n",value);
		return;
	}
			
	for(i=++heap->Size;(i!=1)&&(heap->Element[i/2]) < value; i/=2)
	{
		heap->Element[i] = heap->Element[i/2];
	}		
	heap->Element[i]=value;
	printf("insert %d\n",value);
}

int Find(Heap heap, int value)
{	
	for (int i=1; i <= heap->Size; i++)
	{
		if (value==heap->Element[i])
			return 1;
	}
	return 0;
}

int DeleteMax(Heap heap)
{
	if(heap->Size==0)
	{
		printf("Deletion Error: Max Heap is empty !\n");
		return 0;
	}
	int i, child, MaxElement, LastElement;

	MaxElement= heap->Element[1];
	LastElement= heap->Element[heap->Size--];

	for(i=1; i*2<=heap->Size; i = child)
	{
		child=i*2;
		if(child != heap->Size && heap->Element[child+1] > heap->Element[child])
			child++;
		
		if(LastElement< heap->Element[child])
			heap->Element[i] = heap->Element[child];
		else
			break;
	}
	heap->Element[i]=LastElement;
	printf("Max Element: %d deleted\n",MaxElement);
	return MaxElement;
}

void PrintHeap(Heap heap)
{
	int index, i;
	int count = 0;
	
	if(heap->Size==0)
	{
		printf("Print Error : Max heap is empty!\n");
		return;
	}
	for(index = 1; index <= heap->Size; index++)
	{
		printf("%d ", heap->Element[index]);
	}
	printf("\n");
}
