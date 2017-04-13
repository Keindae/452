/*
* Matt Noblett
* Ben Commet
* Lab 12 - File System Interface
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    if(argc != 3){
        printf("You did not input the correct amount of inputs. Please input a valid ls option followed by the directory you wish to list\n");
        exit(0);
    }
    char * type = argv[1];
    mydir = opendir(argv[2]);
    if(mydir == NULL){
        printf("%s\n", "The directory entered is invalid");
        exit(0);
    }
    char buf[1024];
    if(strcmp(type, "-l") == 0){
        while((myfile = readdir(mydir)) != NULL){
            sprintf(buf, "%s/%s", argv[2], myfile->d_name);
            stat(buf, &mystat);
            if(myfile->d_name[0] != '.'){
                printf("%jd",mystat.st_size);
                printf(" %s\n", myfile->d_name);
            }
        }
    }
    else if (strcmp(type, "-i") == 0){
        while((myfile = readdir(mydir)) != NULL){
            sprintf(buf, "%s/%s", argv[2], myfile->d_name);
            stat(buf, &mystat);
            if(myfile->d_name[0] != '.'){
                printf("%jd",mystat.st_ino);
                printf(" %s\n", myfile->d_name);
            }
        }
    }
    else{
        printf("The option you provided for ls was invalid.\n-l for detailed file information\n-i for the file inode\n");
    }
    closedir(mydir);
}
