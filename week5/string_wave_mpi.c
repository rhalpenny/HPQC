#include <mpi.h>
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

void check_args(int argc, char **argv, int rank, Args *args) {
    if (argc != 5) {
        if (rank == 0) {
            fprintf(stderr, "Usage: %s <points> <cycles> <samples> <output_csv>\n", argv[0]);
            fprintf(stderr, "Example: %s 1000 200 10 data/week5/string_wave_mpi.csv\n", argv[0]);
        }
        MPI_Finalize();
        exit(1);
    }

    args->points = atoi(argv[1]);
    args->cycles = atoi(argv[2]);
    args->samples = atoi(argv[3]);
    strncpy(args->output_file, argv[4], sizeof(args->output_file) - 1);
    args->output_file[sizeof(args->output_file) - 1] = '\0';
}

void init_full_positions(double *full, int points) {
    for (int i = 0; i < points; i++) {
        full[i] = sin((2.0 * M_PI * i) / (points - 1));
    }
}

void exchange_boundaries(double *local, int local_n, int rank, int size) {
    MPI_Status status;
    double left_recv = 0.0, right_recv = 0.0;

    if (rank > 0) {
        MPI_Sendrecv(&local[1], 1, MPI_DOUBLE, rank - 1, 0,
                     &left_recv, 1, MPI_DOUBLE, rank - 1, 1,
                     MPI_COMM_WORLD, &status);
        local[0] = left_recv;
    }

    if (rank < size - 1) {
        MPI_Sendrecv(&local[local_n], 1, MPI_DOUBLE, rank + 1, 1,
                     &right_recv, 1, MPI_DOUBLE, rank + 1, 0,
                     MPI_COMM_WORLD, &status);
        local[local_n + 1] = right_recv;
    }
}

void update_positions(double *local, double *next, int local_n, int rank, int size) {
    for (int i = 1; i <= local_n; i++) {
        if ((rank == 0 && i == 1) || (rank == size - 1 && i == local_n)) {
            next[i] = local[i];
        } else {
            next[i] = 0.5 * (local[i - 1] + local[i + 1]);
        }
    }
}

int main(int argc, char **argv) {
    int rank, size;
    Args args;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    check_args(argc, argv, rank, &args);

    if (args.points % size != 0) {
        if (rank == 0) fprintf(stderr, "Error: points must be divisible by number of processes\n");
        MPI_Finalize();
        return 1;
    }

    int local_n = args.points / size;

    double *full = NULL;
    double *gathered = NULL;
    double *local = malloc((local_n + 2) * sizeof(double));
    double *next = malloc((local_n + 2) * sizeof(double));

    if (rank == 0) {
        full = malloc(args.points * sizeof(double));
        gathered = malloc(args.points * sizeof(double));
        init_full_positions(full, args.points);
    }

    MPI_Scatter(full, local_n, MPI_DOUBLE, &local[1], local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    FILE *fp = NULL;
    if (rank == 0) {
        fp = fopen(args.output_file, "w");
        if (fp == NULL) {
            fprintf(stderr, "Error opening output file\n");
            MPI_Finalize();
            return 1;
        }
        fprintf(fp, "cycle,point,value\n");
    }

    for (int cycle = 0; cycle < args.cycles; cycle++) {
        if (cycle % args.samples == 0) {
            MPI_Gather(&local[1], local_n, MPI_DOUBLE, gathered, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

            if (rank == 0) {
                for (int i = 0; i < args.points; i++) {
                    fprintf(fp, "%d,%d,%f\n", cycle, i, gathered[i]);
                }
            }
        }

        exchange_boundaries(local, local_n, rank, size);
        update_positions(local, next, local_n, rank, size);

        for (int i = 1; i <= local_n; i++) {
            local[i] = next[i];
        }
    }

    if (rank == 0) {
        fclose(fp);
        free(full);
        free(gathered);
    }

    free(local);
    free(next);

    MPI_Finalize();
    return 0;
}
