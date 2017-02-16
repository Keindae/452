
//Matt Noblett
//Ben Commet
//Lab 5- Winter 2017 Wolffe
//Reader is supposed to read in what the writer has written to it and display it.

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define MEMORY_SIZE 4096
void exit_handler (int sigNum);
//gobal ids and pointers
int shmId, flId;
char *string_mem;
int *flag_mem;
int main(){
	//Listen for ^C
	signal (SIGINT, exit_handler);
	//Local ids and memory variables
	int shmid;
	key_t key, flag_key;
	char *s;
	key = 4444;
	flag_key = 1234;
	//Grab a section of memory for the strings
	if((shmid = shmget(key, MEMORY_SIZE, 0666)) < 0){
		perror("shmget failed");
		exit(1);
	}
	//Attach to the string memory
	if((string_mem = shmat(shmid, NULL, 0)) == (char *) - 1){
		perror("shmat failed");
		exit(1);
	}
	//Grab a section of memory for the flags
	if((flId = shmget(flag_key, MEMORY_SIZE, 0666)) < 0){
		perror("shmget failed");
		exit(1);
	}
	//Attach to the flag memory
	if((flag_mem = shmat(flId, NULL, 0)) == (void *) - 1){
		perror("shmat failed");
		exit(1);
	}
	//Reader ID is used to tell which of the two readers we are using
	int readerId;
	if(flag_mem[2] == 0){
		readerId = 0;
		flag_mem[2] = 1;
	}
	else{ readerId = 1;}

	//This loop runs until the user inputs a new word to be read
	while(1){
		//If reader 0 and the flag for reader 0 isn't read then output the string
		if(readerId == 0 && flag_mem[0] == 0){
			for(s = string_mem; *s != NULL; s++){
				putchar(*s);
			}
			flag_mem[0] = 1;
		}
		//If reader 1 and the flag for reader 0 isn't read then output the string
		if(readerId && flag_mem[1] == 0){
			for(s = string_mem; *s != NULL; s++){
				putchar(*s);
			}
			flag_mem[1] = 1;
		}
	}
	//Detatch from the memory
	shmdt(string_mem);
	shmdt(string_mem);
	exit(0);
}

//Exit the program and detatch from the memory
void exit_handler (int sigNum)
{
	shmdt(string_mem);
	shmdt(flag_mem);
	printf ("That's it, I'm shutting you down\n");
	exit(0);
}
