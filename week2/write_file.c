#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./write_file <number_of_lines>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    const char *filename = "/home/ug/halpenr4/data/week2/output_c.txt";

    clock_t start_time = clock();

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not open file for writing.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "This is line %d\n", i);
    }

    fclose(fp);

    clock_t end_time = clock();
    double run_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Wrote %d lines to %s\n", n, filename);
    printf("Runtime: %.6f seconds\n", run_time);

    return 0;
}
