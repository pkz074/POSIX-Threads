#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


typedef struct student{

    char name[20];
    int student_id;
    float grade;

} students;

void* bellcurve(void* arg) {

    students *s = (students *)arg;
    s->grade *= 1.5;
    if (s->grade > 100.0)
        s->grade = 100.0;
    printf("Name: %s | Student ID:  %d | Grade:  %.2f\n", s->name, s->student_id, s->grade);


    return NULL;
}
int main(void) {


    students ss[5];
    pthread_t pt[5];

    for (size_t t = 0; t < 5; t++){
        printf("For student %zu\n", t+1);
        printf("Please enter the name, student number and grade ");
        fflush(stdout);
        scanf("%s" "%d" "%f", ss[t].name, &ss[t].student_id, &ss[t].grade);
    }

    for (size_t t = 0; t<5; t++){

        pthread_create(&pt[t], NULL, bellcurve, &ss[t]);
    }

    for (size_t t = 0; t < 5; t++) {

        pthread_join(pt[t], NULL);
    }
}
