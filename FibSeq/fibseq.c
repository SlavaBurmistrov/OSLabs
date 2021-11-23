#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
//Fibonacc
int n;
int* fibseq;
void* fibonacci(void* arg);

int main(int argc, char* argv[]) {
	n = atoi(argv[1]); //Number for fib seq
	fibseq = (int *)malloc(n * sizeof(int)); //Alocate mem
	//Thread stuff starts here 
	pthread_t tid; 
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,fibonacci,NULL);
	pthread_join(tid,NULL);
	//Thread stuff end here
	printf("The Seq : ");
	for(int k=0; k<n; k++){
	printf("%d ", fibseq[k]); //Run the fibonacci code
	}
	    printf("\n");
		return 0;
}
void* fibonacci(void* arg){
		fibseq[0]=0; //First number of fib
		fibseq[1]=1; //Second number of fib
		for(int i=2; i<n;i++){ //The rest of the numbers
		fibseq[i]=fibseq[i-1]+fibseq[i-2];
		}
	pthread_exit(0);
}