#include <stdlib.h>
#include <stdio.h>
#include <alchemy/heap.h>

RT_HEAP stosek;

int main(){
	int a;
	int **arr;
	arr = (int**) malloc(sizeof(int*));
	arr[0] = (int*) malloc(2*sizeof(int));
	char name[100] = "stosik";
	rt_heap_create(&stosek, name, sizeof(char), H_SINGLE);
	for(int i=0; a!=1; i++){
		printf("podaj czas trwania: ");
		scanf("%d", &arr[i][0]);
		printf("dziena chuju teraz priorytet: ");
		scanf("%d", &arr[i][1]);
		printf("idziesz dalej chuju dodawac gowno? 0 - tak, 1 - nie: ");
		scanf("%d", &a);
		if(a!=1){
			arr = realloc(arr, (i+2)*sizeof(int*));
			arr[i+1] = (int*)malloc(2*sizeof(int));
		}
		printf("czas: %d\t priorytet: %d\n", arr[i][0], arr[i][1]);
		
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<2;j++){
			printf("%d\n", arr[i][j]);
		}
	}
}
