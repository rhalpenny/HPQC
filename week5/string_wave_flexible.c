#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int points;
    int cycles;
    int samples;
    char output_file[256];
} Args;

void check_args(int argc, char **argv, Args *args) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <points> <cycles> <samples> <output_csv>\n", argv[0]);
        fprintf(stderr, "Example: %s 50 100 100 data/week5/string_wave_flexible.csv\n", argv[0]);
        exit(1);
    }

    args->points = atoi(argv[1]);
    args->cycles = atoi(argv[2]);
    args->samples = atoi(argv[3]);
    strncpy(args->output_file, argv[4], sizeof(args->output_file) - 1);
    args->output_file[sizeof(args->output_file) - 1] = '\0';

    if (args->points < 3 || args->cycles < 1 || args->samples < 1) {
        fprintf(stderr, "Error: points must be >= 3, cycles >= 1, samples >= 1\n");
        exit(1);
    }
}

void init_positions(double *current, int points) {
    for (int i = 0; i < points; i++) {
        current[i] = sin((2.0 * M_PI * i) / (points - 1));
    }
}

void update_positions(double *current, double *next, int points) {
    next[0] = current[0];
    next[points - 1] = current[points - 1];

    for (int i = 1; i < points - 1; i++) {
        next[i] = current[i + 1];
    }
}

void write_frame(FILE *fp, int cycle, double *current, int points) {
    for (int i = 0; i < points; i++) {
        fprintf(fp, "%d,%d,%f\n", cycle, i, current[i]);
    }
}

int main(int argc, char **argv) {
    Args args;
    check_args(argc, argv, &args);

    double *current = malloc(args.points * sizeof(double));
    double *next = malloc(args.points * sizeof(double));

    if (current == NULL || next == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return 1;
    }

    FILE *fp = fopen(args.output_file, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open output file %s\n", args.output_file);
        free(current);
        free(next);
        return 1;
    }

    fprintf(fp, "cycle,point,value\n");

    init_positions(current, args.points);

    for (int cycle = 0; cycle < args.cycles; cycle++) {
        if (cycle % args.samples == 0) {
            write_frame(fp, cycle, current, args.points);
        }

        update_positions(current, next, args.points);

        double *temp = current;
        current = next;
        next = temp;
    }

    fclose(fp);
    free(current);
    free(next);

    return 0;
}
