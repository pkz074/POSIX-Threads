#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* hello_world();
void* goodbye();

int main(void) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, *hello_world, "Thread 1");
    pthread_create(&t2, NULL, *goodbye, "Thread 2");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}

void* hello_world() {
    int random_num = rand();
    sleep(random_num%3);
    printf("Hello World");
    return NULL;
}

void* goodbye() {
    int random_num = rand();
    sleep(random_num%3);
    printf("Goodbye");
    return NULL;
}