#include<stdio.h>
#include<stdlib.h>

struct TreeStruct{
	int Size;
	int nodeNum;
	int* Element;
};
typedef struct TreeStruct * Tree;

Tree CreateTree(int treeSize);
void Insert(Tree tree, int value);
void printTree(Tree tree);
void printPreorder(Tree tree, int index);
void printInorder(Tree tree, int index);
void printPostorder(Tree tree, int index);

void main(int argc, char* argv[])
{
	FILE *fi;
	Tree tree;
	int treeSize;
	int tempNum;

	fi=fopen(argv[1], "r");
	fscanf(fi,"%d", &treeSize);
	tree = CreateTree(treeSize);
	while(fscanf(fi,"%d",&tempNum)==1)
	{
		Insert(tree, tempNum);
	}
	printTree(tree);
}

Tree CreateTree(int treeSize){
	Tree tree = malloc(sizeof(struct TreeStruct));
	tree->Element = malloc(sizeof(int)*(treeSize+1));
	tree->Size = treeSize;
	tree->nodeNum=1;
	return tree;
}

void Insert(Tree tree, int value){
	if(tree->nodeNum>tree->Size){
		printf("Full Tree\n");
		return;}
	tree->Element[tree->nodeNum++]=value;
}

void printTree(Tree tree){
	printf("Preoder: ");
	printPreorder(tree,1);
	printf("\nInorder: ");
	printInorder(tree,1);
	printf("\nPostorder: ");
	printPostorder(tree,1);
	printf("\n");
	free(tree->Element);
	free(tree);
}

void printInorder(Tree tree, int index){
	if (2*index<=tree->Size)
		printInorder(tree, index*2);
	printf("%d ", tree->Element[index]);
	if (2*index+1<=tree->Size)	
		printInorder(tree, index*2+1);
}

void printPreorder(Tree tree, int index){
	if (index<=tree->Size){
		printf("%d ", tree->Element[index]);
		printPreorder(tree, index*2);
		printPreorder(tree, index*2+1);}
}

void printPostorder(Tree tree, int index){
	if (index<=tree->Size){
		printPostorder(tree, index*2);
		printPostorder(tree, index*2+1);
		printf("%d ", tree->Element[index]);
	}
}
