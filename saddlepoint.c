#include <stdio.h>
#define ROW 3
#define COL 3
int main() {
    int matrix[ROW][COL] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int i, j;
    int found = 0;
    for (i = 0; i < ROW; i++) {
        // Find the minimum in the current row
        int minRow = matrix[i][0];
        int colIndex = 0;
        for (j = 1; j < COL; j++) {
            if (matrix[i][j] < minRow) {
                minRow = matrix[i][j];
                colIndex = j;
            }
        }
        // Check if minRow is the maximum in its column
        int isSaddle = 1;
        for (int k = 0; k < ROW; k++) {
            if (matrix[k][colIndex] > minRow) {
                isSaddle = 0;
                break;
            }
        }
        if (isSaddle) {
            printf("Saddle point found: %d at row %d, column %d\n", minRow, i, colIndex);
            found = 1;
        }
    }
    if (!found)
        printf("No saddle point found.\n");

    return 0;
}
