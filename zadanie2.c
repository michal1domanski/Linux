#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>
#include <alchemy/heap.h>
#include <alchemy/mutex.h>

RT_TASK zadania[3];
RT_TASK task;
RT_HEAP stos;
RT_SEM sem;
int licznik;

void serve(void *arg) {
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);

	printf("%s utworzone. \n", info.name);

	while(1) {
		printf("%s czeka na semafor.\n", info.name);
		rt_sem_p(&sem, TM_INFINITE);
		printf("%S otrzymalo semafor.\n", info.name);

		printf("%s ustawia licznik na %i.\n", info.name, ++licznik);

		rt_task_wait_period(NULL);

		rt_sem_v(&sem);
		printf("%s zwolnilo semafor.\n", info.name);
	}
}

int globalna = 0;

void fun(void *arg) {
	globalna = globalna + 1;
	printf("globalna = %d\n", globalna);
	rt_timer_spin((*((long long*)(arg))));
}

int main(int a, char** b) {
	mlockall(MCL_CURRENT | MCL_FUTURE);
	printf("czekam na sterte\n");
	RT_HEAP heap;
	rt_heap_bind(&heap, "myheap", TM_INFINITE);

	printf("czekam na mutex\n");
	RT_MUTEX mutex;
	rt_mutex_bind(&mutex, "mymutex", TM_INFINITE);

	unsigned long long int* ptr;
	char lastmod = 0;
	rt_heap_alloc(&heap, 0, TM_INFINITE, (void**)&ptr);
	SRTIME start;
	SRTIME end;
	int i = 1;
	while(1){
		rt_mutex_acquire(&mutex, TM_INFINITE);
		if (ptr[0] != lastmod) {
			start = rt_timer_ticks2ns(rt_timer_read());
			printf("rozpoczecie zadania %d = %llu\n", i, start);
			RT_TASK task;
			rt_task_create(&task, "zadanie", 0, ptr[1], 0);
			rt_task_set_periodic(&task, TM_NOW, TM_NOW+ptr[0]);
			rt_task_start(&task, &fun, &ptr[0]);
			printf("czas: %llu, priorytet: %d\n", ptr[0], ptr[1]);
			ptr[0] = lastmod;
			end = rt_timer_ticks2ns(rt_timer_read());
			printf("zakonczenie zadania %d = %llu\n", i, end);
			i = i + 1;
		}
		rt_mutex_release(&mutex);
		rt_task_sleep(1000000000LL);
	}

	/*char name[3][10];
	sprintf(name[0], "zad 1");
	sprintf(name[1], "zad 2");
	sprintf(name[2], "zad 3");
	for(int i=0;i<3;i++){
		char name[10];
		snprintf(name, 5, "zad %d",i);
		rt_task_create(&zadania[i], name[i], 0, 10, 0);
		rt_task_set_periodic(&zadania[i], TM_NOW, 5000000000LL);
		rt_task_start(&zadania[i], &fromheap, 0);
	}*/

	pause();
}





