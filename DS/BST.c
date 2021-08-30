#include<stdio.h>
#include<stdlib.h>

typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
	int value;
	Tree left;
	Tree right;
};

Tree insertNode(Tree root, int key);
void findNode(Tree root, int key);
void printInorder(Tree root);
Tree deleteNode(Tree root, int key);
Tree getMaxValueInTree(Tree parentNode,Tree root);

void main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1],"r");
	char cv;
	int key;

	Tree root = NULL;

	while (!feof(fi)){
		fscanf(fi, "%c",&cv);
		switch(cv){
		case 'i':
			fscanf(fi,"%d", &key);
			root = insertNode(root, key);
			break;
		case 'd':
			fscanf(fi, "%d", &key);
			deleteNode(root,key);
			break;
		case 'f':
			fscanf(fi, "%d", &key);
			findNode(root, key);
			break;
		case 'p':
			fscanf(fi,"%c",&cv);
			if (cv=='i')
				printInorder(root);
			printf("\n");
			break;
		}

	}
}

Tree insertNode(Tree root, int key){
	if (root ==NULL)
	{
		root=malloc(sizeof(struct BinarySearchTree));
		root->value=key;
		root->left=root->right=NULL;
		printf("insert %d\n",key);
	}
	else if (key<root->value)
		root->left = insertNode(root->left, key);
	else if (key>root->value)
		root->right = insertNode(root->right, key);
	else
	{
		printf("There is already %d in the tree.\n",key);
		return root;
	}
	return root;
}

Tree deleteNode(Tree root, int key){
	Tree TmpCell;
	
	if (root==NULL)
		printf("Deletion Error: %d is not in the tree.\n",key);
	else if (key<root->value)
		root->left=deleteNode(root->left,key);
	else if (key>root->value)
		root->right=deleteNode(root->right,key);
	else if (root->left && root->right)
	{
		printf("delete %d\n",root->value);
		TmpCell=getMaxValueInTree(root->left,root);
		root->value=TmpCell->value;
		root->left=deleteNode(root->left,root->value);
	}
	else
	{
		TmpCell=root;
		if (root->left==NULL)
			root=root->right;
		else if (root->right==NULL)
			root=root->left;
		free(TmpCell);
	}
	return root;

}

void findNode(Tree root, int key){
	if (root==NULL)
	{
		printf("%d is not in the tree\n",key);
		return;
	}
	if (key<root->value)
		findNode(root->left,key);
	else if (key>root->value)
		findNode(root->right,key);
	else
	{
		printf("%d is in the tree.\n",key);
		return;
	}
}

void printInorder(Tree root){
	if (root)
	{
		printInorder(root->left);
		printf("%d ", root->value);
		printInorder(root->right);
	}
}

Tree getMaxValueInTree(Tree parentNode, Tree root){
	if(root==NULL)
		return NULL;
	else
	{
		while(parentNode->right!=NULL)
			parentNode=parentNode->right;
	}
	return parentNode;
}
