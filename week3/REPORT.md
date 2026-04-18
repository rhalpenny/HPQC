# Week 3 Report: Introduction to MPI

## Objective
To explore parallel programming using MPI and compare performance with serial implementations.

## MPI Hello World
The MPI program launches multiple processes. Each process prints its rank and total number of processes.

Observation:
- Increasing number of processes increases total CPU usage
- user + sys time exceeds real time → confirms parallelism

## proof.c Analysis
- Root node gathers results
- Worker nodes compute partial results
- Uses send/receive model

Equivalent:
- Could be replaced by direct summation formula

## Serial Vector
- Performs computation sequentially
- Runtime increases linearly with vector size

## Parallel Vector
- Vector divided across processes
- Each process computes partial sum
- MPI_Reduce combines results

## Comparison
- Small inputs: serial faster (low overhead)
- Large inputs: MPI can become faster
- Performance depends on:
  - number of processes
  - communication overhead
  - workload size

## Conclusion
MPI allows parallel computation but introduces overhead. It is beneficial only when workload is large enough to offset communication costs.

