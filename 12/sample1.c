#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[])
{
   struct stat statBuf;

   if (argc < 2) {
      printf ("Usage: filename required\n");
      exit(1);
   }

   if (stat (argv[1], &statBuf) < 0) {
      perror ("huh?  there is ");
      exit(1);
   }

  if(statBuf.st_mode == 16877){
      printf("Yo homes, it's a directory\n" );
  }
  else{
      printf("Like OMG it's totally not a directory LOL :) <3\n");
  }
   return 0;
}
