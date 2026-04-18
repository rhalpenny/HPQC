#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) printf("Usage: %s <size>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    int n = atoi(argv[1]);
    int local_n = n / size;

    double *local_vec = malloc(local_n * sizeof(double));

    // Fill local chunk
    for (int i = 0; i < local_n; i++) {
        int global_index = rank * local_n + i;
        local_vec[i] = global_index * 0.5;
    }

    double local_sum = 0.0;
    for (int i = 0; i < local_n; i++) {
        local_sum += local_vec[i] * local_vec[i];
    }

    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Total sum = %f\n", global_sum);
    }

    free(local_vec);
    MPI_Finalize();
    return 0;
}
