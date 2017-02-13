#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h>
#include <time.h>
#include <string.h>

#define MEMORY_SIZE 4096

void exit_handler (int sigNum);
int main(){
	//Listen for ^C 
	signal (SIGINT, exit_handler);
	char input[256];
	

	while(1){
		fprintf(stderr, "Enter string: ");
		//Get input from user
		fgets(input, 256, stdin);
		//Spawn in a new in the rand_sleep method and send it our user input
		fprintf(stderr, "%s\n", input);
		
	}
	return 0;
}

void exit_handler (int sigNum) 
{ 
	printf ("That's it, I'm shutting you down\n"); 
	exit(0); 
}
