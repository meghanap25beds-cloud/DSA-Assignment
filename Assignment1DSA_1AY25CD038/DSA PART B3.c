#include <stdio.h>
#include <math.h>
typedef struct {
    int degree;
    float coef[101];
} polynomial;
polynomial readPolynomial(void) {
    polynomial p;
    int i;

    printf("Enter degree of polynomial (0-100): ");
    scanf("%d", &p.degree);

    /* Validate the degree */
    if (p.degree < 0 || p.degree > 100) {
        printf("Invalid degree!\n");
        p.degree = -1;
        return p;
    }

    /* Read coefficients from highest power to constant */
    for (i = 0; i <= p.degree; i++) {
        printf("Enter coefficient of x^%d: ",
               p.degree - i);
        scanf("%f", &p.coef[i]);
    }

    return p;
}

/* Function to add two polynomials */
polynomial add(polynomial a, polynomial b) {
    polynomial result;
    int exponent;
    float ca, cb;

    /* Result degree is the greater of the two degrees */
    if (a.degree > b.degree)
        result.degree = a.degree;
    else
        result.degree = b.degree;

    /* Add coefficients having matching exponents */
    for (exponent = 0;
         exponent <= result.degree;
         exponent++) {

        ca = 0.0;
        cb = 0.0;

        /* Get coefficient from first polynomial */
        if (exponent <= a.degree)
            ca = a.coef[a.degree - exponent];

        /* Get coefficient from second polynomial */
        if (exponent <= b.degree)
            cb = b.coef[b.degree - exponent];

        /* Store the sum at the correct position */
        result.coef[result.degree - exponent] = ca + cb;
    }

    /* Remove leading zero coefficients */
    while (result.degree > 0 &&
           fabs(result.coef[0]) < 0.000001) {

        int i;

        /* Shift coefficients one position to the left */
        for (i = 0; i < result.degree; i++) {
            result.coef[i] = result.coef[i + 1];
        }

        result.degree--;
    }

    return result;
}

/* Function to display a polynomial */
void display(polynomial p) {
    int i, exponent;
    int printed;
    float c;

    printed = 0;

    /* Traverse coefficients from highest power to constant */
    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        exponent = p.degree - i;

        /* Skip zero coefficients */
        if (fabs(c) < 0.000001)
            continue;

        /* Print the correct sign */
        if (printed) {
            if (c > 0)
                printf(" + ");
            else
                printf(" - ");
        } else if (c < 0) {
            printf("-");
        }

        /* Do not print coefficient 1 for x or x^n */
        if (fabs(fabs(c) - 1.0) > 0.000001 ||
            exponent == 0) {
            printf("%g", fabs(c));
        }
        if (exponent > 1)
            printf("x^%d", exponent);
        else if (exponent == 1)
            printf("x");

        printed = 1;
    }
    if (!printed)
        printf("0");

    printf("\n");
}
int main(void) {
    polynomial a, b, sum;
    printf("\nEnter first polynomial:\n");
    a = readPolynomial();

    if (a.degree == -1)
        return 1;

    /* Read the second polynomial */
    printf("\nEnter second polynomial:\n");
    b = readPolynomial();

    if (b.degree == -1)
        return 1;

    sum = add(a, b);
    printf("\nFirst polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    printf("Sum of polynomials: ");
    display(sum);

    return 0;
}

