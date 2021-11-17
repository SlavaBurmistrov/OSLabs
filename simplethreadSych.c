#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//synced version
int SharedVariable = 0;

pthread_mutex_t mutex;
pthread_barrier_t barr;
void* SimpleThread(int which) {
	int num, val;
	for(num = 0; num < 20; num++) {
		pthread_mutex_lock(&mutex);
		if (random() > RAND_MAX / 2)
			usleep(10);
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", which, val);
		SharedVariable = val + 1;
		pthread_mutex_unlock(&mutex);
		}
		pthread_barrier_wait(&barr);
		val = SharedVariable;
	printf("Thread %d sees final value %d\n", which, val);
}

int main(int argc, char* argv[]) {
	int t = 3;
    pthread_t th[t];
	pthread_mutex_init(&mutex,NULL);
    pthread_barrier_init(&barr, NULL, t);
    int i;
    for (i = 0; i < t; i++) {
        if (pthread_create(th + i, NULL, *SimpleThread, i) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < t; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }
	pthread_mutex_destroy(&mutex);
    return 0;
}