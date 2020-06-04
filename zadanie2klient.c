#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <alchemy/heap.h>
#include <alchemy/sem.h>
#include <alchemy/mutex.h>

const int TASK_MAX = 55;

typedef union{
	struct{
		uint64_t prio, time;
	};
	long long ind;
}task_data;


int main(int a, char** b){
	printf("czekam na sterte\n");
	RT_HEAP heap;
	rt_heap_bind(&heap, "myheap", TM_INFINITE);
	printf("czekam na mutex\n");
	RT_MUTEX mutex;
	rt_mutex_bind(&mutex, "mymutex", TM_INFINITE);
	printf("czekam na semafor\n");
	RT_SEM sem;
	rt_sem_bind(&sem, "mysem", TM_INFINITE);
	task_data* ptr;
	rt_heap_alloc(&heap, 0, TM_INFINITE, (void**)&ptr);
	while(1){
		task_data usr_inp;
		printf("podaj czas trwania: ");
		scanf("%llu", &usr_inp.time);
		printf("podaj priorytet: ");
		scanf("%d", &usr_inp.prio);
		rt_mutex_acquire(&mutex, TM_INFINITE);
		long long ind = ++ptr[0].ind;
		if(ind == TASK_MAX) {
			ind = 1;
			ptr[0].ind = ind;
		}
		ptr[ind] = usr_inp;
		rt_mutex_release(&mutex);
		rt_sem_v(&sem);
	}
}
