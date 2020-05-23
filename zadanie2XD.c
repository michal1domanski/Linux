#include <stdlib.h>
#include <stdio.h>
#include <alchemy/pipe.h>

int main(){
	int a;
	int **arr;
	arr = (int**) malloc(sizeof(int*));
	arr[0] = (int*) malloc(2*sizeof(int));

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
		char name ="array";
		rt_pipe_create(&arr, &name, P_MINOR_AUTO, 0);
	}
}
