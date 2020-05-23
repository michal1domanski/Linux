#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>

RT_TASK zadania[2];

int globalna = 0;

void fun1(void *arg) {
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	while(1) {
		(*((int*)(arg)))++;
		printf("%s = %i\n", info.name, *((int*)(arg)) );
			
			rt_task_wait_period(NULL);
	}
}
void fun2(void *arg) {
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	while(1) {
		globalna--;
		printf("%s = %i\n", info.name, globalna );
			rt_task_wait_period(NULL);
	}
}
int main(int a, char** b) {
	int lokalna = 0;
	mlockall(MCL_CURRENT | MCL_FUTURE);
	
	char name[10];
	sprintf(name, "lokalna");
	rt_task_create(&zadania[0], name, 0, 10, 0);
	sprintf(name,"globalna");
	rt_task_create(&zadania[1], name, 0, 10, 0);
	
	rt_task_set_periodic(&zadania[0], TM_NOW, 5000000000LL);
	rt_task_set_periodic(&zadania[1], TM_NOW, 5000000000LL);
	
	rt_task_start(&zadania[0], &fun1, &lokalna);
	rt_task_start(&zadania[1], &fun2, NULL);

	pause();
}
