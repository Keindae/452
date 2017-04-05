#include <Windows.h>
#include <stdio.h>
#define KB 1024

void displayMemInfo(MEMORY_BASIC_INFORMATION memInfo);
int main() {
  SYSTEM_INFO systemInfo;
  MEMORY_BASIC_INFORMATION memInfo;
  GetSystemInfo(&systemInfo);

  printf("Page Size is: %d\n", systemInfo.dwPageSize);
  char *data;
  int bytes = (1024*1024);
  data = (char *) malloc(bytes);
  for(int i=0;i<bytes;i++){
   data[i] = (char) rand();
  }

  sizeof(memInfo) == VirtualQuery(data, &memInfo, sizeof(memInfo));
  displayMemInfo(memInfo);
  free(data);
  sizeof(memInfo) == VirtualQuery(data, &memInfo, sizeof(memInfo));
  displayMemInfo(memInfo);
  return 0;
}

void displayMemInfo(MEMORY_BASIC_INFORMATION memInfo){
  if(memInfo.State == 4096){
    printf("The memory's state is committed.\n" );
  }
  else if(memInfo.State == 65536){
    printf("The memory's state is free\n");
  }
  else if(memInfo.State == 8192){
    printf("The memory's state is reserved");
  }
  else{
    printf("The state of memory is %ld an unexpected value\n", memInfo.State);
  }
}
