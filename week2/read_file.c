#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    const char *filename = "/home/ug/halpenr4/data/week2/output_c.txt";
    char buffer[256];
    int line_count = 0;

    clock_t start_time = clock();

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file for reading.\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        line_count++;
    }

    fclose(fp);

    clock_t end_time = clock();
    double run_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Read %d lines from %s\n", line_count, filename);
    printf("Runtime: %.6f seconds\n", run_time);

    return 0;
}
