
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
int shmId, flId;
char *shared_mem;
int *flag_mem;
int main(){
	int shmid;
	key_t key, flag_key;
	char *s;
	key = 4444;
	flag_key = 1234;
	signal (SIGINT, exit_handler);

	if((shmid = shmget(key, MEMORY_SIZE, 0666)) < 0){
		perror("shmget failed");
		exit(1);
	}

	if((shared_mem = shmat(shmid, NULL, 0)) == (char *) - 1){
		perror("shmat failed");
		exit(1);
	}

	if((flId = shmget(flag_key, MEMORY_SIZE, 0666)) < 0){
		perror("shmget failed");
		exit(1);
	}

	if((flag_mem = shmat(flId, NULL, 0)) == (void *) - 1){
		perror("shmat failed");
		exit(1);
	}
	int readerId;
	if(flag_mem[2] == 0){
		readerId = 0;
		flag_mem[2] = 1;
	}
	else{ readerId = 1;}
	printf("%d\n", readerId);
	while(1){
		if(readerId == 0 && flag_mem[0] == 0){
			for(s = shared_mem; *s != NULL; s++){
				putchar(*s);
			}
			flag_mem[0] = 1;
		}
		if(readerId && flag_mem[1] == 0){
			for(s = shared_mem; *s != NULL; s++){
				putchar(*s);
			}
			flag_mem[1] = 1;
		}
	}
	shmdt(shared_mem);
	shmdt(shared_mem);
	exit(0);
}

void exit_handler (int sigNum)
{
	shmdt(shared_mem);
	shmdt(flag_mem);
	printf ("That's it, I'm shutting you down\n");
	exit(0);
}
