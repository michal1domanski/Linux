#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>
#include <alchemy/heap.h>
#include <alchemy/mutex.h>
#include <stdlib.h>

const int TASK_MAX = 55;

typedef union{
	struct{
		uint64_t prio, time;
	};
	long long ind;
}task_data;

void fun(void *arg) {
	rt_task_set_mode(0, T_LOCK, NULL);
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	printf("rozpoczecie zadania %s: %llu\n", info.name, rt_timer_read());
	rt_timer_spin((*((uint64_t*)(arg))));
	printf("zakonczenie zadania %s: %llu\n", info.name, rt_timer_read());
}

void fromheap(void *arg){
	printf("czekam na sterte\n");
	RT_HEAP heap;
	rt_heap_create(&heap, "myheap", TASK_MAX*sizeof(task_data), H_SINGLE | H_PRIO);
	printf("czekam na mutex\n");
	RT_MUTEX mutex;
	rt_mutex_create(&mutex, "mymutex");
	printf("czekam na semafor\n");
	RT_SEM sem;
	rt_sem_create(&sem, "mysem", 0, 0);
	task_data* ptr;
	rt_heap_alloc(&heap, 0, TM_INFINITE, (void**)&ptr);
	RT_TASK task[TASK_MAX];
	int zadanie = 0;
	long long ind = 0;

	while(1){
		rt_sem_p(&sem, TM_INFINITE);
		rt_mutex_acquire(&mutex, TM_INFINITE);
		ind = (ind + 1) % TASK_MAX;
		uint64_t *time = malloc(sizeof(uint64_t));
		*time = ptr[ind].time;
		printf("%llu\n", ptr[ind].time);
		char name[12];
		sprintf(name, "zadanie %d", zadanie);
		printf("%s\n", &ptr[ind].time);
		rt_task_create(&task[zadanie], name, 0, ptr[ind].prio, 0);
		rt_task_start(&task[zadanie], &fun, (void*)time);
		rt_mutex_release(&mutex);
		zadanie = (zadanie + 1) % TASK_MAX;
	}
}

int main(int a, char** b) {
	mlockall(MCL_CURRENT | MCL_FUTURE);
	RT_TASK task;
	rt_task_create(&task, "fromtask", 0, 10, 0);
	rt_task_start(&task, &fromheap, NULL);
	pause();
}

