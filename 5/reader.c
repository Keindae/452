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
int main(){
	int shmid;
	key_t key;
	char *shm, *s;

	key = 4321;

	if((shmid = shmget(key, MEMORY_SIZE, 0666)) < 0){
		perror("shmget failed");
		exit(1);
	}

	if((shm = shmat(shmid, NULL, 0)) == (char *) - 1){
		perror("shmat failed");
		exit(1);
	}

	for(s = shm; *s != NULL; s++){
		putchar(*s);
	}
	putchar('\n');

	*shm = '*';

	exit(0);


}
