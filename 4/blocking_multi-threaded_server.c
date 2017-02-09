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
char *totalString;
int main(){
	signal (SIGINT, exit_handler);
	char input[256];
    srand(time(NULL));
    int status;
	fprintf(stderr, "Input files: ");
	while(1){
		fgets(input, 256, stdin);
		pthread_t childThread;
		status = pthread_create(&childThread, NULL, rand_sleep, &input[0]);
		if(status){
			fprintf(stderr, "Error: Thread not started");
		}
		else{
			pthread_detach(childThread);
		}
	}
	return 0;
}

void exit_handler (int sigNum) 
{ 
    int totalfiles = found_on_cache + not_on_cache;
    printf("The total number of files requested: %d\n", totalfiles);
    printf("The total number of files found on disk: %d\n", found_on_cache);
    printf (" received. That's it, I'm shutting you down\n"); 
    exit(0); 
}

void* rand_sleep(void* arg){
	char *arguments;
	arguments= (char*) arg;
	char localArray[strlen(arguments-1)];
	int position = 0;
	while(*(arguments + position)){
		localArray[position] = *(arguments + position);
		position ++;
	}
	if(rand() % 5){
		sleep(1);
		fprintf(stderr, "Found file: %s", &localArray[0]);
		found_on_cache ++;
	}
	//20% of time
	else{
		sleep(rand()% 4 + 7 );
		fprintf(stderr, "Not found in disk cache: %s", &localArray[0]);
		not_on_cache ++;
	}
	return NULL;
	
}
