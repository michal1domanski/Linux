#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>

RT_TASK zadanie;
void obsluga(void *arg) {
	RT_TASK *zadanieptr;
	RT_TASK_INFO zadanieinfo;
	zadanieptr = rt_task_self();
	rt_task_inquire(zadanieptr, &zadanieinfo);

	int i=0;
	while (i++ < 10) {
		printf("%s\n", zadanieinfo.name);
		rt_task_wait_period(NULL);
	}
}
int main(int argc, char* argv[]) {
	mlockall(MCL_CURRENT|MCL_FUTURE);
	char info[20];
	sprintf(info, "Zadanie wykonane");
	rt_task_create(&zadanie, info, 0, 10, 0);
	rt_task_set_periodic(&zadanie, TM_NOW, 10000000000LL);
	rt_task_start(&zadanie, &obsluga, 0);
	pause();
}
