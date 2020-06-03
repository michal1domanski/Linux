#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <alchemy/heap.h>
#include <alchemy/heap.h>
#include <alchemy/mutex.h>

void toheap(void *arg) {
	RT_HEAP heap;

	rt_heap_create(&heap, "myheap", 100, H_SINGLE | H_PRIO);

	RT_MUTEX mutex;
	rt_mutex_create(&mutex, "mymutex");

	uint64_t* ptr;
	rt_heap_alloc(&heap, 0, TM_INFINITE, (void**)&ptr);

	uint64_t **arr;
	arr = (uint64_t**) malloc(sizeof(uint64_t*));
	arr[0] = (uint64_t*) malloc(2*sizeof(uint64_t));
	char name[100] = "stosik";
	int i = 0;
	while(1) {
		printf("podaj czas trwania zadania\n");
		scanf("%llu", &arr[i][0]);
		printf("podaj priorytet zadania\n");
		scanf("%llu", &arr[i][1]);

		arr = realloc(arr, (i+2)*sizeof(uint64_t*));
		arr[i+1] = (uint64_t*)malloc(2*sizeof(uint64_t));

		printf("czas: %llu\t priorytet: %d\n", arr[i][0], arr[i][1]);
		rt_mutex_acquire(&mutex, TM_INFINITE);
		ptr[0] = arr[i][0];
		ptr[1] = arr[i][1];
		rt_mutex_release(&mutex);
		i = i + 1;
	}
}

int main(int a, char** b){
	mlockall(MCL_CURRENT | MCL_FUTURE);

	RT_TASK task;

	rt_task_create(&task, "totask", 0, 10, 0);
	rt_task_start(&task, &toheap, NULL);

	pause();
}
