#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/wait.h>
int launch_process(char **args);
int main(int argc, char **argv){
	int isExit = 0;
	// char exit[4] = "exit";
	char input[51];
	printf("shell> ");
	while(!isExit){
		fgets(input, 50, stdin);
		input[strlen(input) -1] = 0;
		char* checkForSpace = strchr(input, ' ');
		if(checkForSpace == NULL){ 
			strcat(input, " ");
		}
		//This pointer will receive tokens
		int iterator = 0;
		char **tokens = malloc(64 * sizeof(char*));
		char *token;
		token = strtok(input, " ");
		while(token != NULL){
			// runToken(token);
			tokens[iterator] = token;
			iterator ++;
			token = strtok(NULL, " ");
		}
		// printf("%s\n", tokens[1]);
		launch_process(tokens);
	}
	return 0;
}

int launch_process(char **args){
	pid_t pid;
	int status;
	struct rusage childUsage;
	// struct rusage *usage;
	if(strcmp(args[0], "quit") == 0){
		printf("quiting!\n");
		exit(0);
	}
	pid = fork();
	//child process returns zero, if in child process, execute commands
	if (pid == 0){
		if(execvp(args[0], args) == -1){
			fprintf(stderr, "The command entered is invalid\n");
		}
		exit(0);
	}
	else{
		waitpid(-1, &status, 0);
		getrusage(RUSAGE_CHILDREN, &childUsage);
		printf("CPU Time Used: %ld.%06ld\n", childUsage.ru_utime.tv_sec, childUsage.ru_utime.tv_usec);
		printf("Involuntary Context Switches %li\n", childUsage.ru_nivcsw);
	}
	printf("shell>");
	return 0;
}
