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
int shmId;
char *shared_mem;
int main(){
	//Listen for ^C
	signal (SIGINT, exit_handler);
	char input[256];
	key_t key;
	char *s;

	key = 4444;

	if ((shmId = shmget(key, MEMORY_SIZE, IPC_CREAT | 0666)) < 0) {
	        perror("shmget");
	        exit(1);
	 }

	 if ((shared_mem = shmat(shmId, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }


	while(1){
		s = shared_mem;
		fprintf(stderr, "Enter string: ");
		//Get input from user
		fgets(input, 256, stdin);
		//Spawn in a new in the rand_sleep method and send it our user input
		fprintf(stderr, "%s\n", input);

		int i;
		for(i = 0; i < strlen(input); i++){
			*s++ = input[i];
		}

		while (*shared_mem != '*' && *(shared_mem + 1) != 1)
        	sleep(1);

	}

	shmdt(shared_mem);
	shmctl(shmId, IPC_RMID, NULL);
	return 0;
}

void exit_handler (int sigNum)
{
	shmdt(shared_mem);
	shmctl(shmId, IPC_RMID, NULL);
	printf ("That's it, I'm shutting you down\n");
	exit(0);
}
