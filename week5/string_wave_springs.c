#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int points;
    int steps;
    int samples;
    double k;
    double m;
    double dt;
    char output_file[256];
} Args;

void check_args(int argc, char **argv, Args *args) {
    if (argc != 8) {
        fprintf(stderr, "Usage: %s <points> <steps> <samples> <k> <m> <dt> <output_csv>\n", argv[0]);
        fprintf(stderr, "Example: %s 50 500 5 1.0 1.0 0.01 data/week5/string_wave_springs.csv\n", argv[0]);
        exit(1);
    }

    args->points = atoi(argv[1]);
    args->steps = atoi(argv[2]);
    args->samples = atoi(argv[3]);
    args->k = atof(argv[4]);
    args->m = atof(argv[5]);
    args->dt = atof(argv[6]);
    strncpy(args->output_file, argv[7], sizeof(args->output_file) - 1);
    args->output_file[sizeof(args->output_file) - 1] = '\0';
}

void init_positions(double *x, double *v, int n) {
    for (int i = 0; i < n; i++) {
        x[i] = sin((2.0 * M_PI * i) / (n - 1));
        v[i] = 0.0;
    }
    x[0] = 0.0;
    x[n - 1] = 0.0;
}

void write_frame(FILE *fp, int step, double *x, int n) {
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d,%d,%f\n", step, i, x[i]);
    }
}

void update_system(double *x, double *v, double *a, int n, double k, double m, double dt) {
    for (int i = 1; i < n - 1; i++) {
        double left_force = -k * (x[i] - x[i - 1]);
        double right_force = -k * (x[i] - x[i + 1]);
        double force = left_force + right_force;
        a[i] = force / m;
    }

    for (int i = 1; i < n - 1; i++) {
        v[i] += a[i] * dt;
        x[i] += v[i] * dt;
    }

    x[0] = 0.0;
    x[n - 1] = 0.0;
    v[0] = 0.0;
    v[n - 1] = 0.0;
}

int main(int argc, char **argv) {
    Args args;
    check_args(argc, argv, &args);

    double *x = malloc(args.points * sizeof(double));
    double *v = malloc(args.points * sizeof(double));
    double *a = malloc(args.points * sizeof(double));

    if (x == NULL || v == NULL || a == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return 1;
    }

    FILE *fp = fopen(args.output_file, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening output file\n");
        return 1;
    }

    fprintf(fp, "cycle,point,value\n");

    init_positions(x, v, args.points);

    for (int step = 0; step < args.steps; step++) {
        if (step % args.samples == 0) {
            write_frame(fp, step, x, args.points);
        }
        update_system(x, v, a, args.points, args.k, args.m, args.dt);
    }

    fclose(fp);
    free(x);
    free(v);
    free(a);

    return 0;
}
