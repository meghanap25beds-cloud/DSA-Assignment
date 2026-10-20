#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

int main() {
    int n, i;
    float sum = 0, average;
    struct Student *ptr, *temp, *topper;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    // Dynamically allocate memory
    ptr = (struct Student *)malloc(n * sizeof(struct Student));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read student records using pointer arithmetic
    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f",
              &(ptr + i)->roll_no,
              (ptr + i)->name,
              &(ptr + i)->marks);
    }

    // Calculate average and find topper
    topper = ptr;

    for (i = 0; i < n; i++) {
        sum += (ptr + i)->marks;

        if ((ptr + i)->marks > topper->marks) {
            topper = ptr + i;
        }
    }

    average = sum / n;

    printf("\nAverage marks: %.2f\n", average);
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           topper->name, topper->roll_no, topper->marks);

    // Ask whether to add two more students
    char choice;
    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        int old_n = n;
        int new_n = n + 2;

        // Use a temporary pointer with realloc
        temp = (struct Student *)realloc(
            ptr, new_n * sizeof(struct Student));

        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            free(ptr);
            return 1;
        }

        ptr = temp;

        // Read the two additional records
        for (i = old_n; i < new_n; i++) {
            printf("Enter roll, name, marks: ");
            scanf("%d %19s %f",
                  &(ptr + i)->roll_no,
                  (ptr + i)->name,
                  &(ptr + i)->marks);
        }

        n = new_n;
        sum = 0;

        // Recalculate average using all students
        for (i = 0; i < n; i++) {
            sum += (ptr + i)->marks;
        }

        average = sum / n;
        printf("Updated average marks: %.2f\n", average);
    }

    // Free allocated memory
    free(ptr);
    ptr = NULL;

    return 0;
}

