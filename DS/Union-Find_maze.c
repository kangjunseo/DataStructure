#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet{
	int size_maze;
	int *ptr_arr;
} DisjointSets;

void init(DisjointSets *sets, DisjointSets *maze_print, int num);
void union_(DisjointSets *sets, int i ,int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void printMaze(DisjointSets *sets, int num);
void freeMaze(DisjointSets *sets, DisjointSets *maze_print);

int main (int argc, char* argv[]){
	int num,i;
	FILE *fi = fopen(argv[1],"r");
	fscanf(fi, "%d", &num);

	DisjointSets *sets, *maze_print;
	sets=(DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print=(DisjointSets*)malloc(sizeof(DisjointSets));

	init(sets,maze_print,num);
	createMaze(sets,maze_print,num);
	printMaze(maze_print,num);
	freeMaze(sets,maze_print);

	return 0;
}

void init(DisjointSets *sets, DisjointSets *maze_print, int num){
	sets->size_maze=maze_print->size_maze=num*num;
	sets->ptr_arr=malloc(sizeof(int)*(sets->size_maze+1));
	maze_print->ptr_arr=malloc(sizeof(int)*(2*maze_print->size_maze+1));

	for (int i = 1; i<=sets->size_maze;i++){
		sets->ptr_arr[i]=0;
	}

	for (int i = 1; i<2*maze_print->size_maze+1; i++){
		maze_print->ptr_arr[i]=-1;
	}
}

void union_(DisjointSets *sets, int i, int j){
	int r1 = find(sets, i);
	int r2 = find(sets, j);

	if (sets->ptr_arr[r2] < sets->ptr_arr[r1])
		sets->ptr_arr[r1]=r2;
	else{
		if (sets->ptr_arr[r1]==sets->ptr_arr[r2])
			sets->ptr_arr[r1]--;
		sets->ptr_arr[r2]=r1;
	}
}

int find(DisjointSets *sets, int i){
	while (sets->ptr_arr[i]>0)
		i = sets->ptr_arr[i];
	return i;
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num){
	srand(time(NULL));
	while (find(sets,1)!=find(sets,num*num)){	
		int rand_num = 1+rand()%(2*num*num);
		if (rand_num<num*num && rand_num%num!=0){
			if (find(sets,rand_num)!=find(sets,rand_num+1)){
				union_(sets,rand_num ,rand_num+1);
				maze_print->ptr_arr[rand_num] = 0;
			}
		}else if(rand_num>num*num && rand_num<=2*num*num-num){
			if (find(sets,rand_num-num*num)!=find(sets,rand_num-num*num+num)){
				union_(sets,rand_num-num*num,rand_num-num*num+num);
				maze_print->ptr_arr[rand_num] = 0;
			}
		}
	}
	maze_print->ptr_arr[num*num]=0;
}

void printMaze(DisjointSets *sets, int num){
	printf(" ");
	for (int i =1; i<=num; i++){
		printf("- ");
	}
	printf("\n");
	int index = 1;
	
	printf(" ");
	for (int i = 1; i<=num; i++){
		if (sets->ptr_arr[i]==-1)
			printf(" |");
		else
			printf("  ");
	}
	printf("\n");
	
	printf(" ");
	for (int i = num*num+1; i<=num*num+num; i++){
		if (sets->ptr_arr[i]==-1)
			printf("- ");
		else
			printf("  ");
	}
	printf("\n");
	
	while(index<num){
		printf("|");
		for (int i =1+num*index; i<=num*(index+1); i++){
			if (sets->ptr_arr[i]==-1)
				printf(" |");
			else 
				printf("  ");
		}
		printf("\n");

		printf(" ");
		for (int i =num*num+1+num*index; i<=num*num+num*(index+1); i++){
			if (sets->ptr_arr[i]==-1)
				printf("- ");
			else
				printf("  ");
		}
		printf("\n");

		index++;
	}
}

void freeMaze(DisjointSets *sets, DisjointSets *maze_print){
	free(sets->ptr_arr);
	free(maze_print->ptr_arr);
	free(sets);
	free(maze_print);
}
