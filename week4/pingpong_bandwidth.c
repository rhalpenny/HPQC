#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double get_time_seconds() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main(int argc, char **argv) {
    int rank, size;
    int num_pings, num_elements;
    double *buffer;
    double start_time, end_time, elapsed_time, avg_time;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 3) {
        if (rank == 0) fprintf(stderr, "Usage: mpirun -np 2 pingpong_bandwidth <num_pings> <num_elements>\n");
        MPI_Finalize();
        return 1;
    }

    if (size != 2) {
        if (rank == 0) fprintf(stderr, "Error: pingpong_bandwidth must run with exactly 2 processes\n");
        MPI_Finalize();
        return 1;
    }

    num_pings = atoi(argv[1]);
    num_elements = atoi(argv[2]);

    buffer = malloc(num_elements * sizeof(double));
    for (int i = 0; i < num_elements; i++) {
        buffer[i] = (double)i;
    }

    start_time = get_time_seconds();

    for (int i = 0; i < num_pings; i++) {
        if (rank == 0) {
            MPI_Send(buffer, num_elements, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(buffer, num_elements, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &status);
        } else {
            MPI_Recv(buffer, num_elements, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
            MPI_Send(buffer, num_elements, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    }

    end_time = get_time_seconds();
    elapsed_time = end_time - start_time;
    avg_time = elapsed_time / num_pings;

    if (rank == 0) {
        printf("num_pings=%d num_elements=%d bytes=%zu elapsed_time=%e avg_time=%e\n",
               num_pings, num_elements, num_elements * sizeof(double), elapsed_time, avg_time);
    }

    free(buffer);
    MPI_Finalize();
    return 0;
}
