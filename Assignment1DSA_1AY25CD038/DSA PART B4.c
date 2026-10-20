#include <stdio.h>
typedef struct {
    int row;
    int col;
    int value;
} term;

/* Function to print a sparse matrix in triple form */
void printTriples(term a[]) {
    int i;

    printf("Row\tColumn\tValue\n");

    /* a[0] is the header, so start from a[1] */
    for (i = 1; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

/* Fast transpose using counting and starting positions */
void fast_transpose(term a[], term b[]) {
    int row_terms[101];
    int starting_pos[101];
    int i, j, num_cols, num_terms;

    num_cols = a[0].col;
    num_terms = a[0].value;

    /* Initialize the count of elements in each column */
    for (i = 0; i < num_cols; i++) {
        row_terms[i] = 0;
    }

    /* Count non-zero elements in each column of A */
    for (i = 1; i <= num_terms; i++) {
        row_terms[a[i].col]++;
    }

    /* Calculate starting positions in the transpose */
    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++) {
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];
    }

    /* Print row_terms array */
    printf("\nrow_terms array:\n");

    for (i = 0; i < num_cols; i++) {
        printf("%d ", row_terms[i]);
    }

    printf("\n");

    /* Print starting_pos array */
    printf("\nstarting_pos array:\n");

    for (i = 0; i < num_cols; i++) {
        printf("%d ", starting_pos[i]);
    }

    printf("\n");

    /* Set the header of the transposed matrix */
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    /* Place each element directly in its correct position */
    for (i = 1; i <= num_terms; i++) {
        j = starting_pos[a[i].col];

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;

        /* Next element belonging to this transposed row */
        starting_pos[a[i].col]++;
    }
}

int main(void) {
    term a[101], b[101];
    int matrix[10][10];
    int rows, cols;
    int i, j, k;

    /* Read the original matrix */
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || rows > 10 ||
        cols <= 0 || cols > 10) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    /* Store matrix dimensions in the header */
    a[0].row = rows;
    a[0].col = cols;
    a[0].value = 0;

    /* Convert the matrix into triples */
    k = 1;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                a[k].row = i;
                a[k].col = j;
                a[k].value = matrix[i][j];
                k++;
            }
        }
    }

    /* Store the number of non-zero elements */
    a[0].value = k - 1;

    /* Display the original matrix triples */
    printf("\nOriginal matrix triples:\n");
    printf("Header: Rows = %d, Columns = %d, "
           "Non-zero terms = %d\n",
           a[0].row, a[0].col, a[0].value);

    printTriples(a);

    fast_transpose(a, b);
    printf("\nTransposed matrix triples:\n");
    printf("Header: Rows = %d, Columns = %d, "
           "Non-zero terms = %d\n",
           b[0].row, b[0].col, b[0].value);

    printTriples(b);

    printf("\nTransposed triples are in row-major order.\n");

    return 0;
}

