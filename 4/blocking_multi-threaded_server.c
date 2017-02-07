/*******************************************************
Matt Noblett and Ben Commet
Lab 4 - Blocking Multi-threaded Server
Program that simulates a multi-threaded file server
*******************************************************/
#include <stdio.h> 
#include <errno.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <pthread.h> 
#include <time.h>
#include <string.h>

//function declarations
void exit_handler (int);
void* rand_sleep (void* arg);
int found_on_cache, not_on_cache;
int main(){
	signal (SIGINT, exit_handler);
	char input[256];
    srand(time(NULL));
    int status;
	while(1){
		fprintf(stderr, "Input a file: ");
		fgets(input, 256, stdin);
		pthread_t childThread;
		status = pthread_create(&childThread, NULL, rand_sleep, &input[0]);
		if(!status){
			fprintf(stderr, "Error: Thread not started");
		}
		else{
			pthread_detatch(childThread);
		}
	}
	return 0;
}

void exit_handler (int sigNum) 
{ 
    printf (" received. That's it, I'm shutting you down\n"); 
    exit(0); 
}

void* rand_sleep(void* arg){
	char *arguments;
	arguments= (char*) arg;
	printf("%s", arguments);

	//80% of time
	if(rand() % 5){
		sleep(1);
		fprintf(stderr, "Found file: %s\n", arguments);
		found_on_cache ++;
	}
	//20% of time
	else{
		sleep(rand()% 4 + 7 );
		printf("File not found in disk cache\n");
		not_on_cache ++;
	}
	return NULL;
	
}