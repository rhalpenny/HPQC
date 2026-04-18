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
    int counter = 0;
    int num_pings;
    double start_time, end_time, elapsed_time, avg_time;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) fprintf(stderr, "Usage: mpirun -np 2 pingpong <num_pings>\n");
        MPI_Finalize();
        return 1;
    }

    if (size != 2) {
        if (rank == 0) fprintf(stderr, "Error: pingpong must run with exactly 2 processes\n");
        MPI_Finalize();
        return 1;
    }

    num_pings = atoi(argv[1]);

    start_time = get_time_seconds();

    while (counter < num_pings) {
        if (rank == 0) {
            MPI_Send(&counter, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Recv(&counter, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        } else {
            MPI_Recv(&counter, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            counter++;
            MPI_Send(&counter, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    end_time = get_time_seconds();
    elapsed_time = end_time - start_time;
    avg_time = elapsed_time / num_pings;

    if (rank == 0) {
        printf("num_pings=%d counter=%d elapsed_time=%e avg_time=%e\n",
               num_pings, counter, elapsed_time, avg_time);
    }

    MPI_Finalize();
    return 0;
}
