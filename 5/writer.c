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
int shmId, flId;
char *shared_meme;
int *flag_meme;
int main(){
	//Listen for ^C
	signal (SIGINT, exit_handler);
	char input[256];
	key_t key, flag_key;
	char *s;

	flag_key = 1234;
	key = 4444;

	if ((shmId = shmget(key, MEMORY_SIZE, IPC_CREAT | 0666)) < 0) {
	        perror("shmget failed");
	        exit(1);
	 }

	 if ((flId = shmget(flag_key, MEMORY_SIZE, IPC_CREAT | 0666)) < 0) {
					 perror("shmget failed");
					 exit(1);
		}

	 if ((shared_meme = shmat(shmId, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
		if ((flag_meme = shmat(flId, NULL, 0)) == (void *) -1) {
         perror("shmat");
         exit(1);
     }


	while(1){
		s = shared_meme;
		fprintf(stderr, "Enter string: ");
		//Get input from user
		fgets(input, 256, stdin);
		//Spawn in a new in the rand_sleep method and send it our user input

		int i;
		for(i = 0; i < strlen(input); i++){
			*s++ = input[i];
		}
		flag_meme[0] = 0;
		flag_meme[1] = 0;
		while (!flag_meme[0] && !flag_meme[1]){
        sleep(1);
		}
	}
	shmdt(shared_meme);
	shmctl(shmId, IPC_RMID, NULL);
	shmdt(flag_meme);
	shmctl(flId, IPC_RMID, NULL);
	return 0;
}

void exit_handler (int sigNum)
{
	shmdt(shared_meme);
	shmctl(shmId, IPC_RMID, NULL);
	shmdt(flag_meme);
	shmctl(flId, IPC_RMID, NULL);
	printf ("That's it, I'm shutting you down\n");
	exit(0);
}
