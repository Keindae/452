#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/shm.h>

#define FOO 4096

int main () 
{ 
   int shmId; 
   char *shmPtr;
<<<<<<< HEAD
   struct shmid_ds test;
=======
   key_t key = 1234;
>>>>>>> f5723f510a0f7b03aa0cbe836e49c0a766305914

   if ((shmId = shmget (key, FOO, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) { 
      perror ("i can't get no..\n"); 
      exit (1); 
   } 
   if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) {
      perror ("can't attach\n"); 
      exit (1); 
   }

   shmctl(shmId, IPC_STAT, &test);
   int size = (int) test.shm_segsz;
   printf("Size of memory: %d or %#x\n", size, size);
   printf ("value a: %lu\t value b: %lu\n", (unsigned long) shmPtr, (unsigned long) shmPtr + FOO);
   if (shmdt (shmPtr) < 0) { 
      perror ("just can't let go\n"); 
      exit (1); 
   } 
   if (shmctl (shmId, IPC_RMID, 0) < 0) { 
      perror ("can't deallocate\n"); 
      exit(1); 
   }


   return 0; 
}


