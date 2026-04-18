# Week 4: MPI Communications

## Overview
This activity investigates MPI communications through point-to-point routines, ping-pong benchmarking, and collective communication methods.

## Files
- comm_test_mpi.c
- comm_test_functional.c
- comm_send_variants.c
- pingpong.c
- pingpong_bandwidth.c
- vector_diy_sendrecv.c
- vector_bcast.c
- vector_scatter_gather.c
- vector_scatter_reduce.c
- vector_custom_reduce.c

## Compilation
```bash
mpicc HPQC/week4/comm_test_mpi.c -o bin/comm_test_mpi
mpicc HPQC/week4/comm_test_functional.c -o bin/comm_test_functional
mpicc HPQC/week4/comm_send_variants.c -o bin/comm_send_variants
mpicc HPQC/week4/pingpong.c -o bin/pingpong
mpicc HPQC/week4/pingpong_bandwidth.c -o bin/pingpong_bandwidth
mpicc HPQC/week4/vector_diy_sendrecv.c -o bin/vector_diy_sendrecv
mpicc HPQC/week4/vector_bcast.c -o bin/vector_bcast
mpicc HPQC/week4/vector_scatter_gather.c -o bin/vector_scatter_gather
mpicc HPQC/week4/vector_scatter_reduce.c -o bin/vector_scatter_reduce
mpicc HPQC/week4/vector_custom_reduce.c -o bin/vector_custom_reduce
