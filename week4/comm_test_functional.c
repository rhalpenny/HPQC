#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_time_seconds() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void check_args(int argc) {
    if (argc != 1) {
        fprintf(stderr, "Usage: mpirun -np N comm_test_functional\n");
    }
}

void root_task(int size) {
    int recv_val;
    MPI_Status status;

    for (int src = 1; src < size; src++) {
        MPI_Recv(&recv_val, 1, MPI_INT, src, 0, MPI_COMM_WORLD, &status);
        printf("Root received %d from rank %d\n", recv_val, src);
    }
}

void client_task(int rank) {
    int send_val = rank * 10;
    MPI_Send(&send_val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    printf("Rank %d sent %d to root\n", rank, send_val);
}

void check_task(int rank, int size) {
    if (rank == 0) {
        root_task(size);
    } else {
        client_task(rank);
    }
}

int main(int argc, char **argv) {
    int rank, size;

    check_args(argc);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    check_task(rank, size);

    MPI_Finalize();
    return 0;
}
