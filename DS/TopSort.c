#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Queue
{
	int size;
	int *key;
	int front;
	int rear;
};

struct _Graph
{
	int size;
	int* node;
	int** matrix;
};

Graph CreateGraph(int X);
void InsertEdge(Graph G, int nodeS, int nodeD);
Queue CreateQueue(int X);
void Enqueue(Queue Q, int item);
int Dequeue(Queue Q);
void Topsort(Graph G);

int main(int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");
	int X, node_s, node_d;
	
	fscanf(fi, "%d", &X);

	Graph G = CreateGraph(X);

	for(int i=0; i<X; i++)
		fscanf(fi, "%d", &G->node[i]);
	
	while(fscanf(fi,"%d %d", &node_s, &node_d) != EOF){
		InsertEdge(G, node_s, node_d);
	}

	Topsort(G);
}

Graph CreateGraph(int X){
	Graph G = malloc(sizeof(Graph));
	G->size=X;
	G->node=malloc(sizeof(int)*G->size);
	G->matrix=malloc(sizeof(int*)*G->size);
	for(int i =0; i<G->size; i++)
		G->matrix[i]=malloc(sizeof(int)*G->size);
	return G;
}

void InsertEdge(Graph G, int nodeS, int nodeD){
	int s = 0;
	int d = 0;
	while(G->node[s] != nodeD)
		s++;
	
	while(G->node[d] != nodeS)
		d++;
	G->matrix[s][d]=1;
}

Queue CreateQueue(int X){
	Queue Q = malloc(sizeof(Queue));
	Q->size = X;
	Q->key = malloc(sizeof(int) * Q->size);
	Q->front =0;
	Q->rear=-1;
	return Q;
}

void Enqueue(Queue Q, int item){
	if (Q->rear == Q->size-1){
		printf("Queue is full.\n");
		return;
	}
	else
		Q->key[++Q->rear]=item;
	return;
}

int Dequeue(Queue Q){
	if (Q->front > Q->rear){
		printf("Queue is empty.\n");
		return 0;
	}
	else
		return Q->key[Q->front++];
}

void Topsort(Graph G){
	Queue Q;
	int V, W;
	int* Indegree=malloc(sizeof(int*)*G->size);

	Q = CreateQueue(G->size);
	for(V=0; V<G->size; V++){
		for(W=0; W<G->size; W++){
				Indegree[V]=Indegree[V]+G->matrix[V][W];
		}
	}

	for(V=0; V<G->size; V++){
		if(Indegree[V]==0)
			Enqueue(Q,V);
	}

	while(Q->front <= Q->rear){
		V=Dequeue(Q);
		printf("%d ",G->node[V]);
		for(W=0; W<G->size; W++){
			if (G->matrix[W][V] == 1 || W==V){
				if (--Indegree[W] == 0)
					Enqueue(Q,W);
			}
		}
	}
}
