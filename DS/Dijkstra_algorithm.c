#include<stdio.h>
#include<stdlib.h>

const int INF = (int)2e9;

typedef struct Node{
	int vertex;
	int dist;
	int prev;
	int visit;
}Node;

typedef struct Graph{
	int size;
	Node* nodes;
	int** matrix;
}Graph;

typedef struct Heap{
	int capacity;
	int size;
	Node* elements;
}Heap;

Graph* createGraph(int size);
Heap* createMinHeap(int heap_size);
void insertToMinHeap(Heap* minHeap, Node newNode);
Node deleteMin(Heap* minHeap);
void printShortestPath(Graph* G);

int main (int argc, char* argv[]){
	FILE *fi = fopen(argv[1], "r");

	int size;
	fscanf(fi, "%d", &size);
	
	Graph* G = createGraph(size);

	int node_s, node_d, weight;
	while(fscanf(fi,"%d %d %d", &node_s, &node_d, &weight) != EOF){
		G->matrix[node_s][node_d]=weight;
	}

	printShortestPath(G);
	return 0;
}

Graph* createGraph(int size){
	Graph* G = malloc(sizeof(Graph*));
	G->size = size;
	G->nodes = malloc(sizeof(Node)*(size+1));
	G->matrix = malloc(sizeof(int*)*(size+1));
	for(int i=1; i<=size; i++){
		G->matrix[i]=malloc(sizeof(int)*(size+1));
		G->nodes[i].vertex=i;
		G->nodes[i].dist=INF;
		G->nodes[i].prev=i;
		G->nodes[i].visit=0;
	}
	return G;
}

Heap* createMinHeap(int heap_size){
	Heap* heap = malloc(sizeof(Heap*));
	heap->capacity=heap_size;
	heap->size=0;
	heap->elements=malloc(sizeof(Node)*(heap_size+1));
	return heap;
}

void insertToMinHeap(Heap* minHeap, Node newNode){
	int i;
	if (minHeap->size>=minHeap->capacity)
		return;
	for(i=++minHeap->size; i!=1&& minHeap->elements[i].dist>minHeap->elements[i/2].dist; i/=2){
		minHeap->elements[i] = minHeap->elements[i/2];}
	minHeap->elements[i]=newNode;
}

Node deleteMin(Heap* minHeap){
	int i,Child;
	Node min_element,last_element;
	min_element=minHeap->elements[1];
	last_element=minHeap->elements[minHeap->size--];
	
	for(i =1; i*2<=minHeap->size;i=Child){
		Child=i*2;
		if(Child != minHeap->size && minHeap->elements[Child+1].dist<minHeap->elements[Child].dist)
			Child++;
		if(last_element.dist>minHeap->elements[Child].dist)
			minHeap->elements[i] = minHeap->elements[Child];
		else
			break;
	}

	minHeap->elements[i]=last_element;
	return min_element;
}

void printShortestPath(Graph* G){
	Heap* minHeap = createMinHeap(G->size);
	
	G->nodes[1].dist = 0;
	insertToMinHeap(minHeap,G->nodes[1]);
	while(minHeap->size!=0){
		Node currentNode = deleteMin(minHeap);
		if (currentNode.visit!=0)
			continue;
		currentNode.visit++;
		for(int i = 1; i<=G->size;i++){
			if(G->matrix[currentNode.vertex][i]!=0){
				if(currentNode.dist+G->matrix[currentNode.vertex][i]<G->nodes[i].dist){ //if distance need to be updated
					G->nodes[i].dist=currentNode.dist+G->matrix[currentNode.vertex][i];
					G->nodes[i].prev=currentNode.vertex;
					insertToMinHeap(minHeap,G->nodes[i]);
				}
			}
		}
	}

	for(int i=2; i<=G->size;i++){
		printf("%d",i);
		if(G->nodes[i].dist!=INF){
		for(int j=i;j!=1; j=G->nodes[j].prev){
			printf("<-%d",G->nodes[j].prev);
		}
		printf(" cost: %d\n",G->nodes[i].dist);
		}else{
			printf(" can not be reached.\n");
		}
	}
}
