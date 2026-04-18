# Week 3: Introduction to MPI

## Overview
This activity introduces MPI (Message Passing Interface) for parallel computing. It includes:
- MPI Hello World
- Analysis of MPI program (proof.c)
- Serial vs parallel vector operations
- Benchmarking performance

## Programs
- hello_mpi.c
- vector_serial.c
- vector_mpi.c

## Compilation
```bash
mpicc HPQC/week3/hello_mpi.c -o bin/hello_mpi
mpicc HPQC/week3/vector_mpi.c -o bin/vector_mpi
gcc HPQC/week3/vector_serial.c -o bin/vector_serial
mpirun -np 4 bin/hello_mpi
mpirun -np 4 bin/vector_mpi 100000
./bin/vector_serial 100000
