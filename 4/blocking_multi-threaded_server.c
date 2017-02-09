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
//These two variables keep track of the number of files found on and off the cache
int found_on_cache, not_on_cache;

int main(){
	//Listen for ^C 
	signal (SIGINT, exit_handler);
	char input[256];
	//Seed our random number
   	srand(time(NULL));
    	int status;
	fprintf(stderr, "Input files: ");
	//Continue to accept new files from user
	while(1){
		//Get input from user
		fgets(input, 256, stdin);
		pthread_t childThread;
		//Spawn in a new in the rand_sleep method and send it our user input
		status = pthread_create(&childThread, NULL, rand_sleep, &input[0]);
		if(status){
			fprintf(stderr, "Error: Thread not started");
		}
		//Detatch the child if there aren't any errors in creating the thread
		else{
			pthread_detach(childThread);
		}
	}
	return 0;
}

void exit_handler (int sigNum) 
{ 
  	//Calculate the total number of files
	int totalfiles = found_on_cache + not_on_cache;
	//Print our our stats and let the user know we are exiting
    	printf("The total number of files requested: %d\n", totalfiles);
    	printf("The total number of files found on disk: %d\n", found_on_cache);
    	printf ("That's it, I'm shutting you down\n"); 
    	exit(0); 
}

void* rand_sleep(void* arg){
	char *arguments;
	//Cast the void* arguments to a char*
	arguments= (char*) arg;
	//Create a variable in the local scope that cannot be modified by the other threads
	char localArray[strlen(arguments)];
	if(strlen(arguments) -1 == 0){
		localArray[0] = '\0';
	}
	int position = 0;
	//Until we hit the end of the pointer add the char at the current position
	while(*(arguments + position)){
		localArray[position] = *(arguments + position);
		position ++;
	}
	//End character for string
	localArray[position + 1] = '\0';
	//80% of the time sleep for one second
	if(rand() % 5){
		sleep(1);
		fprintf(stderr, "Found file: %s", &localArray[0]);
		found_on_cache ++;
	}
	//20% of time sleep for 7 to 10 seconds
	else{
		sleep(rand()% 4 + 7 );
		fprintf(stderr, "Not found in disk cache: %s", &localArray[0]);
		not_on_cache ++;
	}
	return NULL;
	
}
