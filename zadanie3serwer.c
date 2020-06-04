#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>
#include <alchemy/heap.h>
#include <alchemy/mutex.h>
#include <stdlib.h>

const int TASK_MAX = 50;

typedef union{
	struct{
		uint64_t start,duration, deadline;
	};
	long long ind;
}task_data;

typedef struct wezel{
	struct {
		uint64_t start, duration, deadline;
	};
	struct wezel* next;
}node_data;

void edf(node_data* node, node_data** node_head){
	if(*node_head == NULL) {
		*node_head = node;
		return;
	}

	if((*node_head) -> deadline > node -> deadline){
		node -> next = *node_head;
		*node_head = node;
	}

	node_data* ptr = *node_head;

	while(ptr -> next != NULL){
		if(ptr -> next -> deadline > node -> deadline){
			node -> next = ptr -> next;
			ptr -> next = node;
			return;
		}
		ptr = ptr -> next;
	}
	ptr -> next = node;
	node -> next = NULL;
	return;
}

node_data* prev_task(node_data* node_head, node_data* zadanie){
	node_data* ptr = node_head;
	while(ptr -> next != zadanie) {
		ptr = ptr -> next;
	}
	return ptr;
}

void fun(void *arg) {
	rt_task_set_mode(0, T_LOCK, NULL);
	RT_TASK_INFO info;
	rt_task_inquire(rt_task_self(), &info);
	node_data* zadanie = (node_data*)arg;
	printf("rozpoczecie zadania %s: %llu\n", info.name, rt_timer_read());
	rt_timer_spin(zadanie -> duration);
	printf("zakonczenie zadania %s: %llu\n", info.name, rt_timer_read());
}

void fromheap(void *arg){
	printf("czekam na sterte\n");
	RT_HEAP heap;
	rt_heap_create(&heap, "myheap", TASK_MAX * sizeof(task_data), H_SINGLE | H_PRIO);
	printf("czekam na mutex\n");
	RT_MUTEX mutex;
	rt_mutex_create(&mutex, "mymutex");
	printf("czekam na semafor\n");
	RT_SEM sem;
	rt_sem_create(&sem, "mysem", 0, 0);

	task_data* ptr;
	node_data* node_head = NULL;
	node_data* zad = NULL;
	rt_heap_alloc(&heap, 0, TM_INFINITE, (void**)&ptr);
	ptr[0].ind = 0;
	RT_TASK zadanie;

	while(1){
		if(zad != NULL) {
			rt_task_join(&zadanie);
			if(zad == node_head) {
				node_head = zad -> next;
			} else {
				node_data* prev = prev_task(node_head, zad);
				prev -> next = zad -> next;
			}
			zad = NULL;
		}
		rt_mutex_acquire(&mutex, TM_INFINITE);
		int time = rt_timer_read();
		while(ptr[0].ind != 0) {
			rt_sem_p(&sem, TM_INFINITE);
			int ind = ptr[0].ind--;
			node_data* node = malloc(sizeof(node_data));
			node -> start = ptr[ind].start;
			node -> duration = ptr[ind].duration;
			node -> deadline = ptr[ind].deadline + time;
			node -> next = NULL;
			edf(node, &node_head);
		}
		rt_mutex_release(&mutex);
		zad = node_head;
		time = rt_timer_read();

		while(zad != NULL && zad -> start > time){
			zad = zad -> next;
		}
		if(zad != NULL){
			char nazwa[12];
			sprintf(nazwa, "zadanie%d", ptr[0].ind);
			rt_task_create(&zadanie, nazwa, 0, 10, T_JOINABLE);
			rt_task_start(&zadanie, &fun, (void*) zad);
		}
	}
}

int main(int a, char** b) {
	mlockall(MCL_CURRENT | MCL_FUTURE);
	RT_TASK task;
	rt_task_create(&task, "from heap", 0, 0, 0);
	rt_task_start(&task, &fromheap, NULL);
	pause();
}

