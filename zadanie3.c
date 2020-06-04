/*wojszwilo debil*/
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <alchemy/task.h>
#include <alchemy/heap.h>
#include <alchemy/mutex.h>
#include <alchemy/sem.h>

typedef union {
	struct {
		uint64_t start, time, deadline;
	};
	int ind;
}task_data;

int main() {
	RT_HEAP hip;
	rt_heap_bind
}
