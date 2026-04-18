#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double get_time_seconds() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void do_send(const char *mode, int value, int rank) {
    MPI_Request request;
    int buffer_size;
    int *buffer;

    if (strcmp(mode, "send") == 0) {
        MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else if (strcmp(mode, "ssend") == 0) {
        MPI_Ssend(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else if (strcmp(mode, "bsend") == 0) {
        buffer_size = MPI_BSEND_OVERHEAD + sizeof(int);
        buffer = malloc(buffer_size);
        MPI_Buffer_attach(buffer, buffer_size);
        MPI_Bsend(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
    } else if (strcmp(mode, "rsend") == 0) {
        MPI_Rsend(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else if (strcmp(mode, "isend") == 0) {
        MPI_Isend(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
    } else {
        if (rank != 0) {
            MPI_Send(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
}

int main(int argc, char **argv) {
    int rank, size;
    int value;
    double start_time, end_time;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2) {
        if (rank == 0) {
            fprintf(stderr, "Usage: mpirun -np N comm_send_variants <send|ssend|bsend|rsend|isend>\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        for (int src = 1; src < size; src++) {
            start_time = get_time_seconds();
            MPI_Recv(&value, 1, MPI_INT, src, 0, MPI_COMM_WORLD, &status);
            end_time = get_time_seconds();
            printf("Root received %d from rank %d in %e seconds\n", value, src, end_time - start_time);
        }
    } else {
        value = rank * 100;
        start_time = get_time_seconds();
        do_send(argv[1], value, rank);
        end_time = get_time_seconds();
        printf("Rank %d using %s took %e seconds to send\n", rank, argv[1], end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
