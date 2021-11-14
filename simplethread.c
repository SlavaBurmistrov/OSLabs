#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int SharedVariable = 0;

void SimpleThread(int which) {
	int num, val;
	for(num = 0; num < 20; num++) {
		if (random() > RAND_MAX / 2)
			usleep(10);
		val = SharedVariable;
		printf("*** thread %d sees value %d\n", which, val);
		SharedVariable = val + 1;
		}
		val = SharedVariable;
	printf("Thread %d sees final value %d\n", which, val);
}

int main(int argc, char* argv[]) {
    pthread_t th[8];
    int i;
    for (i = 0; i < 8; i++) {
        if (pthread_create(th + i, NULL, *SimpleThread, i) != 0) {
            perror("Failed to create thread");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (i = 0; i < 8; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }
    return 0;
}