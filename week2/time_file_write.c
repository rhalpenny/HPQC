#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <number_of_lines> <output_file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    char *filename = argv[2];

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    clock_t start_time = clock();

    for (int i = 0; i < n; i++) {
        fprintf(fp, "This is line %d\n", i);
    }

    fclose(fp);

    clock_t end_time = clock();
    double run_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Wrote %d lines to %s in %f seconds\n", n, filename, run_time);

    return 0;
}
