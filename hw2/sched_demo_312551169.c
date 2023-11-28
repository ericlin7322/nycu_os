#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

typedef struct {
	pthread_t thread_id;
	int thread_num;
	int sched_policy;
	int sched_priority;
} thread_info_t;

pthread_barrier_t barrier;
float time_wait = 0;

void busy_wait(float seconds) {
	clock_t start_time = clock();
	clock_t end_time = start_time + (clock_t) (seconds * CLOCKS_PER_SEC);
	while (clock() < end_time) {
	}
}

void *thread_fun(void *arg) {
	thread_info_t *thread_info = (thread_info_t *) arg;
	pthread_barrier_wait(&barrier);

	for (int i=0;i<3;i++) {
		printf("Thread %d is running\n", thread_info->thread_num);
		busy_wait(time_wait);
	}

	return NULL;
}

int main(int argc, char **argv) {
	int num_thread;
	char *policies;
	char *priorities;

	/* 1. Parse program arguments */
	int opt;
	while ((opt = getopt(argc, argv, "n:t:s:p:")) != -1) {
		switch(opt) {
			case 'n':
				num_thread = atoi(optarg);
				break;
			case 't':
				time_wait = atof(optarg);
				break;
			case 's':
				policies = optarg;
				break;
			case 'p':
				priorities = optarg;
				break;
		}
	}

	int policy[num_thread];
	int priority[num_thread];

	char *p;
	p = strtok(policies, ",");
	for (int i=0;p!=NULL;i++) {
		if (!strcmp(p, "NORMAL"))
			policy[i] = SCHED_OTHER;
		else if (!strcmp(p, "FIFO"))
			policy[i] = SCHED_FIFO;
		p = strtok(NULL, ",");
	}

	p = strtok(priorities, ",");
	for (int i=0;p!=NULL;i++) {
		priority[i] = atoi(p);
		p = strtok(NULL, ",");
	}

	/* 2. Create <num_threads> worker threads */
	thread_info_t thread_info[num_thread];
	pthread_attr_t pthread_attr[num_thread];
	struct sched_param param[num_thread];
	pthread_barrier_init(&barrier, NULL, num_thread+1);

	/* 3. Set CPU affinity */
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(3, &cpuset);
	sched_setaffinity(getpid(), sizeof(cpuset), &cpuset);

	/* 4. Set the attributes to each thread */
	for (int i=0; i<num_thread; i++) {
		pthread_attr_init(&pthread_attr[i]);
		thread_info[i].thread_num = i;
		thread_info[i].sched_policy = policy[i];
		thread_info[i].sched_priority = priority[i];

		param[i].sched_priority = thread_info[i].sched_priority;
		pthread_attr_setinheritsched(&pthread_attr[i], PTHREAD_EXPLICIT_SCHED);
		pthread_attr_setschedpolicy(&pthread_attr[i], thread_info[i].sched_policy);
		pthread_attr_setschedparam(&pthread_attr[i], &param[i]);
		pthread_create(&thread_info[i].thread_id, &pthread_attr[i], thread_fun, (void *)&thread_info[i]);
		pthread_setaffinity_np(thread_info[i].thread_id, sizeof(cpu_set_t), &cpuset);
	}

	/* 5. Start all threads at once */
	pthread_barrier_wait(&barrier);
	
	
	/* 6. Wait for all threads to finish  */ 
	for (int i=0;i<num_thread;i++) {
		pthread_join(thread_info[i].thread_id, NULL);
	}

	pthread_barrier_destroy(&barrier);

	return 0;
}

