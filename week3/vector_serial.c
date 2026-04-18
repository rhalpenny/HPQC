#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    double *vec = malloc(n * sizeof(double));

    // Fill vector with non-trivial values
    for (int i = 0; i < n; i++) {
        vec[i] = i * 0.5;
    }

    clock_t start = clock();

    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += vec[i] * vec[i];  // non-trivial operation
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Sum = %f\n", sum);
    printf("Internal time = %f seconds\n", time_spent);

    free(vec);
    return 0;
}
