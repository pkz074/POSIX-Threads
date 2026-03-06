#define _XOPEN_SOURCE 600

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_STUDENTS 10

double total_grade = 0.0;
pthread_mutex_t mutex;

typedef struct {
    int student_id;
    double grade;
} ThreadArg;

void *class_total(void *arg) {
    ThreadArg *data = (ThreadArg *)arg;

    pthread_mutex_lock(&mutex);
    total_grade += data->grade;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(void) {
    pthread_t threads[NUM_STUDENTS];
    ThreadArg args[NUM_STUDENTS];

    FILE *file = fopen("grades-2.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: could not open grades-2.txt\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (fscanf(file, "%lf", &args[i].grade) != 1) {
            fprintf(stderr, "Error: could not read grade %d from grades-2.txt\n", i + 1);
            fclose(file);
            return EXIT_FAILURE;
        }
        args[i].student_id = i + 1;
    }
    fclose(file);

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_STUDENTS; i++) {
        if (pthread_create(&threads[i], NULL, class_total, &args[i]) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i + 1);
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Total grade of all students: %.2f\n", total_grade);
    printf("Class average: %.2f\n", total_grade / NUM_STUDENTS);

    return EXIT_SUCCESS;
}
