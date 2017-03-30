#include <stdio.h>
#include <stdlib.h>

int test();
int test2();
int test3();
int x;
int y;
int main(){
	printf("f: %p, s: %p\n", &x, &y);
	printf("first variable: %p\n", &test);
	printf("second variable: %p\n", &test2);
	printf("third variable: %p\n", &test3);
	return 0;

}

int test(){
	return 2;
}
int test2(){
	return 1;
}
int test3(){
	return 1;
}

