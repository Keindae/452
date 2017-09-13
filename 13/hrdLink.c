/**********************************************************************
* Matt Noblett and Ben Commet
* Lab 13 - implementing ln in c
* Takes an option (either -h for hard or -s for soft) and creates a
* link between two files whose names are passed as parameters
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
void symLink(const char *, const char *);
void hardLink(const char *, const char *);
int main(int argc, char const *argv[]) {
    /* code */
    if(argc != 4){
        printf("%s\n", "The number of input paramaters is incorrect");
        exit(0);
    }
    if(!strcmp(argv[1], "-s")){
        symLink(argv[2], argv[3]);
    }
    else if(!strcmp(argv[1], "-h")){
        hardLink(argv[2], argv[3]);
    }
    else {
        printf("%s\n", "use -s for Symbolic links and -h for hard links");
    }
    return 0;
}
void symLink(const char * newname, const char * oldname){
    if(symlink(newname, oldname)){
        printf("%s\n", "The files were not successfully linked");
        exit(0);
    }
    else{
        printf("%s\n", "Symbolic Link successful");
    }
}

void hardLink(const char * newname, const char * oldname){
    if(link(newname, oldname)){
        printf("%s\n", "The files were not successfully linked");
    }
    else{
        printf("%s\n", "Hard Link successful");
    }
}
