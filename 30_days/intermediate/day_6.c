#include <stdio.h>
#include <stdlib.h>

// Function to create a dynamically allocated matrix
int** createMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

// Function to free the dynamically allocated matrix
void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to input matrix elements
void inputMatrix(int** matrix, int rows, int cols) {
    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Function to multiply matrices
int** multiplyMatrices(int** mat1, int** mat2, int rows1, int cols1, int cols2) {
    int** result = createMatrix(rows1, cols2);
    
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return result;
}

// Function to display matrix
void displayMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows1, cols1, rows2, cols2;
    
    // Input dimensions for first matrix
    printf("Enter dimensions of first matrix (rows cols): ");
    scanf("%d %d", &rows1, &cols1);
    
    // Input dimensions for second matrix
    printf("Enter dimensions of second matrix (rows cols): ");
    scanf("%d %d", &rows2, &cols2);
    
    // Check if multiplication is possible
    if (cols1 != rows2) {
        printf("Matrix multiplication not possible!\n");
        return 1;
    }
    
    // Create matrices
    int** matrix1 = createMatrix(rows1, cols1);
    int** matrix2 = createMatrix(rows2, cols2);
    
    // Input matrices
    printf("For first matrix:\n");
    inputMatrix(matrix1, rows1, cols1);
    printf("For second matrix:\n");
    inputMatrix(matrix2, rows2, cols2);
    
    // Multiply matrices
    int** result = multiplyMatrices(matrix1, matrix2, rows1, cols1, cols2);
    
    // Display result
    printf("Resultant matrix:\n");
    displayMatrix(result, rows1, cols2);
    
    // Free allocated memory
    freeMatrix(matrix1, rows1);
    freeMatrix(matrix2, rows2);
    freeMatrix(result, rows1);
    
    return 0;
}
