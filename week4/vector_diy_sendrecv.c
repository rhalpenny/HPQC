#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int rank, size, n, local_n;
    double *full_vec = NULL, *local_vec, local_sum = 0.0, total_sum = 0.0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) fprintf(stderr, "Usage: mpirun -np N vector_diy_sendrecv <size>\n");
        MPI_Finalize();
        return 1;
    }

    n = atoi(argv[1]);
    local_n = n / size;
    local_vec = malloc(local_n * sizeof(double));

    if (rank == 0) {
        full_vec = malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) full_vec[i] = i * 0.5;

        for (int dest = 1; dest < size; dest++) {
            MPI_Send(full_vec + dest * local_n, local_n, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
        }

        for (int i = 0; i < local_n; i++) local_vec[i] = full_vec[i];
    } else {
        MPI_Recv(local_vec, local_n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
    }

    for (int i = 0; i < local_n; i++) {
        local_sum += local_vec[i] * local_vec[i];
    }

    if (rank == 0) {
        total_sum = local_sum;
        for (int src = 1; src < size; src++) {
            MPI_Recv(&local_sum, 1, MPI_DOUBLE, src, 1, MPI_COMM_WORLD, &status);
            total_sum += local_sum;
        }
        printf("Total sum = %f\n", total_sum);
        free(full_vec);
    } else {
        MPI_Send(&local_sum, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
    }

    free(local_vec);
    MPI_Finalize();
    return 0;
}
