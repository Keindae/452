#include <windows.h>
#include <stdio.h>

int main(){
    __int64 start_counter= 0;
    double frequency = 0.0;
    int i;
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li)){
        printf("Query performance frequency done broke\n");
        exit(0);
    }
    printf("Frequency of high-resolution Counter: %lf\n", double(li.QuadPart));
    printf("Miliseconds per tick: %lf\n", 1000.0/double(li.QuadPart));
    frequency = double(li.QuadPart)/1000.0;
    QueryPerformanceCounter(&li);
    start_counter = li.QuadPart;

    for(i = 0; i < 1000000; i++){
        ;
    }
    QueryPerformanceCounter(&li);
    printf("%lf\n", double(li.QuadPart - start_counter)/frequency);

    LARGE_INTEGER temp;
    QueryPerformanceCounter(&li);
    start_counter = li.QuadPart;
    QueryPerformanceCounter(&li);
    printf("%lf\n", double(li.QuadPart - start_counter)/frequency);
}
