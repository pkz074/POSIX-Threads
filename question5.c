#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_barrier_t barrier;
void* read_grades(void* arg);
void* save_bellcurve(void* arg);


int grades[10];
int total_grade;
float total_bellcurve;
pthread_mutex_t grade_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int *grades_array;
    int thread_id;
} thread_data_t;

int main(void) {
    pthread_t reader, t2;
    pthread_barrier_init(&barrier, NULL, 1);


    pthread_create(&reader, NULL, read_grades, NULL);
    pthread_barrier_wait(&barrier);

    pthread_join(reader, NULL);

    pthread_t workers[10];

    for (int i =0; i<10; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&workers[i], NULL, save_bellcurve, id);
    }

    FILE *file = fopen("bellcurve.txt", "w");
    fprintf(file, "%g\n", total_bellcurve);
    fclose(file);

    for (int i =0; i<10; i++) {
        pthread_join(workers[i], NULL);
    }

    printf("%d\n", total_grade);
    printf("%g\n", total_bellcurve);
}


void* read_grades(void* arg) {
    //int *grades = (int*)arg;
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

void* save_bellcurve(void* arg) {
    int this_id = *(int*)arg;

    int grade = grades[this_id];

    pthread_mutex_lock(&grade_mutex);

    total_grade += grade;
    total_bellcurve += grade*1.5;
    pthread_mutex_unlock(&grade_mutex);
    free(arg);
    return NULL;
}