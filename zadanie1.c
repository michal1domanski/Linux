#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <malloc.h>

#include <alchemy/task.h>
#include <alchemy/timer.h>

RT_TASK zadania[10];

int zadanie1 = 0;

int zadanie2 = 0;

int zadanie3 = 0;

int zadanie4 = 0;

int zadanie5 = 0;

int zadanie6 = 0;

int zadanie7 = 0;

int zadanie8 = 0;

int zadanie9 = 0;

int zadanie0 = 0;

FILE *file;

SRTIME start[10];

SRTIME end[10];

/*slipuj czas w momencie wejscia w funkcje o podana w pliku txt wartosc (mat[i][0])*/

void fun1(void *arg) {
	start[0] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 1: %llu\n",start[0]);
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie1++;
		/*printf("%s = %i\n", info.name, zadanie1 );*/

			rt_task_wait_period(NULL);
	}
	end[0] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 1: %llu\n",end[0]);
}
void fun2(void *arg) {
	start[1] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 2: %llu\n",start[1]);
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie2--;
		/*printf("%s = %i\n", info.name, zadanie2 );*/
			rt_task_wait_period(NULL);
	}
	end[1] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 2: %llu\n",end[1]);
}
void fun3(void *arg) {
	start[2] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 3: %llu\n",start[2]);
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie3++;
		/*printf("%s = %i\n", info.name, zadanie3 );*/
			rt_task_wait_period(NULL);
	}
	end[2] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 3: %llu\n",end[2]);
}
void fun4(void *arg) {
	start[3] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 4: %llu\n",start[3]);	
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie4--;
		/*printf("%s = %i\n", info.name, zadanie4 );*/
			rt_task_wait_period(NULL);
	}
	end[3] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 4: %llu\n",end[3]);
}
void fun5(void *arg) {
	start[4] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 5: %llu\n",start[4]);
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie5++;
		/*printf("%s = %i\n", info.name, zadanie5 );*/
			rt_task_wait_period(NULL);
	}
	end[4] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 5: %llu\n",end[4]);
}
void fun6(void *arg) {
	start[5] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 6: %llu\n",start[5]);
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie6--;
		/*printf("%s = %i\n", info.name, zadanie6 );*/
			rt_task_wait_period(NULL);
	}
	end[5] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 6: %llu\n",end[5]);
}
void fun7(void *arg) {
	start[6] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 7: %llu\n",start[6]);
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie7++;
		/*printf("%s = %i\n", info.name, zadanie7 );*/
			rt_task_wait_period(NULL);
	}
	end[6] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 7: %llu\n",end[6]);
}
void fun8(void *arg) {
	start[7] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 8: %llu\n",start[7]);
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie8--;
		/*printf("%s = %i\n", info.name, zadanie8 );*/
			rt_task_wait_period(NULL);
	}
	end[7] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 8: %llu\n",end[7]);
}
void fun9(void *arg) {
	start[8] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 9: %llu\n",start[8]);
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie9++;
		/*printf("%s = %i\n", info.name, zadanie9 );*/
			rt_task_wait_period(NULL);
	}
	end[8] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 9: %llu\n",end[8]);
}
void fun0(void *arg) {
	start[9] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas rozpoczecia zadania 0: %llu\n",start[9]);
	int i;
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	for(i=0;i<*(int*)arg;i++) {
		zadanie0--;
		/*printf("%s = %i\n", info.name, zadanie0 );*/
			rt_task_wait_period(NULL);
	}
	end[9] = rt_timer_ticks2ns(rt_timer_read());
	printf("Czas zakonczenia zadania 0: %llu\n",end[9]);
}

typedef void (*FunctionCallback)();
FunctionCallback functions[] = {&fun0, &fun1, &fun2, &fun3, &fun4, &fun5, &fun6, &fun7, &fun8, &fun9};

int main(int a, char** b) {
	int i;
	int j;

	long** mat=malloc(10*sizeof(long*));
	for(i=0;i<10;i++)
		mat[i]=malloc(4*sizeof(long));

	int lokalna = 0;
	mlockall(MCL_CURRENT | MCL_FUTURE);

	file=fopen("zadanie1.txt", "r");
	for(i=0; i<10; i++){
		for(j=0;j<4;j++){
			if (!fscanf(file,"%li", &mat[i][j]))
				break;
		}
	}
	fclose(file);

	for(i=0;i<10;i++){
		char name[10];
		snprintf(name, 10, "zadanie%d", i);
		rt_task_create(&zadania[i], name, 0, mat[i][2], 0);
	}

	for(i=0;i<10;i++){
		rt_task_set_periodic(&zadania[i], mat[i][0], mat[i][1]);
	}

	rt_timer_spin(1000000000);

	for(i=0; i<10; i++){
		rt_task_start(&zadania[i], functions[i], &mat[i][3]);
	}

	pause();

	return 0;
}
