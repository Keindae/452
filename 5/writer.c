//Matt Noblett
//Ben Commet
//Lab 5 - Winter 2017 Wolffe
//Writer takes a user input, and then sends it to a reader for it to display, using shared memory

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
char *shared_mem;
int *flag_mem;
int main(){
	//Listen for ^C
	signal (SIGINT, exit_handler);
	//Local ids and memory variables
	char input[256];
	key_t key, flag_key;
	char *s;
	flag_key = 1234;
	key = 4444;
	//Grab a section of memory for the strings
	if ((shmId = shmget(key, MEMORY_SIZE, IPC_CREAT | 0666)) < 0) {
	        perror("shmget failed");
	        exit(1);
	}
	//Grab a section of memory for the flags
	if ((flId = shmget(flag_key, MEMORY_SIZE, IPC_CREAT | 0666)) < 0) {
					 perror("shmget failed");
					 exit(1);
	}
	//Attach to the string memory
	if ((shared_mem = shmat(shmId, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
	
	//Attach to the flag memory
	if ((flag_mem = shmat(flId, NULL, 0)) == (void *) -1) {
         perror("shmat");
         exit(1);
     }

    //Set the reader indentification flag to 0
	flag_mem[2] = 0;
	while(1){
		//Use temporary pointer to avoid modifying shared mem.
		s = shared_mem;
		fprintf(stderr, "Enter string: ");
		//Get input from user
		fgets(input, 256, stdin);
		int i;
		//Add each character to memory
		for(i = 0; i < strlen(input); i++){
			*s++ = input[i];
		}
		//let the reader know that they have stuff to do
		flag_mem[0] = 0;
		flag_mem[1] = 0;
		//Wait for the readers
		while (!flag_mem[0] && !flag_mem[1]){
        sleep(1);
		}
	}
	//Detatch and delete all memory segments
	shmdt(shared_mem);
	shmctl(shmId, IPC_RMID, NULL);
	shmdt(flag_mem);
	shmctl(flId, IPC_RMID, NULL);
	return 0;
}

//Exit the program and detatch from the memory and delete the memory chunks
void exit_handler (int sigNum)
{
	//Detatch and delete all memory segments
	shmdt(shared_mem);
	shmctl(shmId, IPC_RMID, NULL);
	shmdt(flag_mem);
	shmctl(flId, IPC_RMID, NULL);
	printf ("That's it, I'm shutting you down\n");
	exit(0);
}
