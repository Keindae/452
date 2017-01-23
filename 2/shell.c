#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int isExit = 0;
	// char exit[4] = "exit";
	char input[51];
	while(!isExit){
		fgets(input, 50, stdin);
		input[strlen(input) -1] = 0;
		char* checkForSpace = strchr(input, ' ');
		if(checkForSpace == NULL){ 
			strcat(input, " ");
			printf("%s\n", input);
		}
		//This pointer will recieve tokens
		char *token;
		token = strtok(input, " ");
		while(token != NULL){
			runToken(token);
			token = strtok(NULL, " ");
		}
	}
}

int runToken(char *token){
	char *ex = "exit";
	if(strcmp(token, ex) == 0){
			printf("exiting\n");
			exit(0);
	}
	else{
		printf("not exit\n");
	}
	execvp(token);
	return 0;
}