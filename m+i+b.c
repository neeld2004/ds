#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    char name[50];
    int roll_no;
    float total_marks;
};

// Swap utility
void swap(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

// Insertion Sort
int insertionSort(struct Student arr[], int n) {
    int swaps = 0;
    for (int i = 1; i < n; i++) {
        struct Student key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j].roll_no > key.roll_no) {
            arr[j + 1] = arr[j];
            j--;
            swaps++;
        }
        arr[j + 1] = key;
    }
    return swaps;
}

// Bubble Sort
int bubbleSort(struct Student arr[], int n) {
    int swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].roll_no > arr[j + 1].roll_no) {
                swap(&arr[j], &arr[j + 1]);
                swaps++;
            }
        }
    }
    return swaps;
}

// Merge function for merge sort
int merge(struct Student arr[], int l, int m, int r) {
    int swaps = 0;
    int n1 = m - l + 1;
    int n2 = r - m;

    struct Student L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i].roll_no <= R[j].roll_no) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            swaps++;
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    return swaps;
}

// Merge Sort
int mergeSort(struct Student arr[], int l, int r) {
    int swaps = 0;
    if (l < r) {
        int m = (l + r) / 2;
        swaps += mergeSort(arr, l, m);
        swaps += mergeSort(arr, m + 1, r);
        swaps += merge(arr, l, m, r);
    }
    return swaps;
}

// Print students
void printStudents(struct Student arr[], int n) {
    printf("\n%-10s %-10s %-10s\n", "Name", "Roll No", "Marks");
    for (int i = 0; i < n; i++)
        printf("%-10s %-10d %-10.2f\n", arr[i].name, arr[i].roll_no, arr[i].total_marks);
}

int main() {
    struct Student students[MAX], temp[MAX];
    int n, choice, swaps;

    printf("Enter number of students: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Roll No: ");
        scanf("%d", &students[i].roll_no);
        printf("Total Marks: ");
        scanf("%f", &students[i].total_marks);
    }

    do {
        printf("\nSorting Options:\n1. Insertion Sort\n2. Bubble Sort\n3. Merge Sort\n4. Exit\nChoose: ");
        scanf("%d", &choice);

        memcpy(temp, students, sizeof(students)); // Copy original array
        switch (choice) {
            case 1:
                swaps = insertionSort(temp, n);
                printStudents(temp, n);
                printf("Total swaps: %d\n", swaps);
                break;
            case 2:
                swaps = bubbleSort(temp, n);
                printStudents(temp, n);
                printf("Total swaps: %d\n", swaps);
                break;
            case 3:
                swaps = mergeSort(temp, 0, n - 1);
                printStudents(temp, n);
                printf("Merge sort comparisons (not actual swaps): %d\n", swaps);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
