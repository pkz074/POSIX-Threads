// 2. Create a program the does the following.
//     - Prompts the professor for five student’s grades.
//     - Creates 5 threads, one for each student.
//     - Each thread uses a function called bellcurve(grade) which takes as an argument the grade and 
//       bellcurves it by multiplying the grade by 1.50 and then printing the bellcurved grade to the terminal.
//     - The program must create the 5 threads and initialize them only after receiving all 5 grades.

#include <pthread.h>
#include <stdio.h>

#define student_nums 5

void* bellcurve(void* arg) {
        float original_grade = *(float*)arg;

        float final_grade = original_grade * 1.50f;

        printf("original grade: %.2f --> Curved grade: %.2f \n", original_grade, final_grade);

        pthread_exit(NULL);
    }

int main() {

    float grades[student_nums];
    pthread_t threads[student_nums];

    // loop and ask fr ogrades and fill it up
    for (int i = 0; i < student_nums; i++) {
        printf("Enter student #%d's grade: ", i+1);
        scanf("%f", &grades[i]);
    }

    // create threads
    for (int i = 0; i < student_nums; i++) {
        pthread_create(&threads[i], NULL, bellcurve, &grades[i]);
    }

    // join threads
    for (int i = 0; i < student_nums; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}