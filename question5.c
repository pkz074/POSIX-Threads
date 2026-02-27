#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_barrier_t barrier;
void* read_grades();

int total_grade;

int main(void) {
    pthread_t t1, t2;

    int grades[10] = {0};

    pthread_create(&t1, NULL, read_grades, (void*)grades);
    pthread_barrier_wait(&barrier);

    pthread_join(t1, NULL);
}


void* read_grades(void* arg) {
    int *grades = (int*)arg;
    FILE *file = fopen("grades-2.txt", "r");

    for (int i = 0; i < 10; i++) {
        // Stop if we run out of numbers before hitting 10
        if (fscanf(file, "%d", &grades[i]) != 1) {
            break; 
        }
    }

    fclose(file);
    return NULL;
}