/*******************************************************
Matt Noblett and Ben Commet
Lab 3 - Interprocess Communication
Spawns off a fork of the child, and then the child will
randomly spawn off signal to the parent. Child waits a certain
amount of time. 
*******************************************************/

#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <signal.h>
#include <time.h>


void sig_handler_parent (int);
void sig_handler_child (int);
void usr1_handler (int);
void usr2_handler (int);

int main() 
{ 
    pid_t pid;
    pid_t parent_pid = getpid();
    pid = fork();
    signal (SIGINT, sig_handler_parent);
    //Check to see if fork worked correctly
    if(pid < 0){
        printf("fork failed");
        exit(1);
    }
    //Parent process
    else if(pid>0){ 
        fprintf(stderr, "parent");
        signal (SIGUSR1, usr1_handler); 
        signal (SIGUSR2, usr2_handler); 
        while(1){
            sleep(1);
        }
    }
    //child process
    else if(pid == 0){
        srand(time(NULL));
        fprintf(stderr, "spawned child PID# %d\n", getpid());
        signal (SIGINT, sig_handler_child);
        while(1){
            fprintf(stderr, "waiting...			");
	    //generate a number between 1 and 5 to use to sleep
            int r = rand()%5 + 1;
            sleep(r);
            if(rand()%2){
                kill(parent_pid, SIGUSR1);
            }
            else{
                kill(parent_pid, SIGUSR2);
            }
        }
    }
    if(pid){ fprintf(stderr, "\nparent\n");}
    else{fprintf(stderr,"\nchild\n");}
    return 0; 
}


void sig_handler_parent (int sigNum) 
{ 
    printf (" received. That's it, I'm shutting you down\n"); 
    exit(0); 
}

void sig_handler_child (int sigNum)
{
   exit(0);
}

void usr1_handler (int sigNum){
    fprintf(stderr, "received a SIGUSR1 signal\n");
}

void usr2_handler (int sigNum){
    fprintf(stderr, "received a SIGUSR2 signal\n");

}
