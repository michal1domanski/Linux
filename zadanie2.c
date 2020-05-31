#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>
#include <alchemy/heap.h>
#include <alchemy/mutex.h>

RT_TASK zadania[3];
RT_HEAP stos;
RT_SEM sem;
int licznik;

void fromheap(void *arg) {
	printf("czekam na sterte\n");
	RT_HEAP heap;
	rt_heap_bind(&heap, "myheap", TM_INFINITE);

	printf("czekam na mutex\n");
	RT_MUTEX mutex;
	rt_mutex_bind(&mutex, "mymutex", TM_INFINITE);
	
	char *ptr;
	char lastmod = 255;
	rt_heap_alloc(&heap, 0, TM_INFINITE, (void**)&ptr);
	while(1){
		rt_mutex_acquire(&mutex, TM_INFINITE);
		if (ptr[2] != 1) {
			printf("%hi, %hi\n", ptr[0], ptr[1]);
		}
		rt_mutex_release(&mutex);
		rt_task_sleep(10000000000LL);
	}
}

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

int main(int a, char** b) {
	mlockall(MCL_CURRENT | MCL_FUTURE);
	
	/*
	char name[3][10];
	sprintf(name[0], "zad 1");
	sprintf(name[1], "zad 2");
	sprintf(name[2], "zad 3");
	for(int i=0;i<3;i++){
		char name[10];
		snprintf(name, 5, "zad %d",i);
		rt_task_create(&zadania[i], name[i], 0, 10, 0);
		rt_task_set_periodic(&zadania[i], TM_NOW, 5000000000LL);
		rt_task_start(&zadania[i], &serve, 0);
	}*/
	RT_TASK task;
	rt_task_create(&task, "fromtask", 0, 10, 0);
	rt_task_start(&task, &fromheap, NULL);


	pause();
}	





