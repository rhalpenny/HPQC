#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int line_count = 0;

    clock_t start_time = clock();

    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        line_count++;
    }

    clock_t end_time = clock();
    fclose(fp);

    double run_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Read %d lines from %s in %f seconds\n", line_count, filename, run_time);

    return 0;
}
