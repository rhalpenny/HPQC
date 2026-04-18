# Week 4 Report: MPI Communications

## 1. Objective
The purpose of this activity was to investigate MPI communications, including point-to-point communication, different send modes, latency and bandwidth measurement, and collective communication methods.

## 2. Part 1: Demonstrating Communications
The original communication test program was compiled and run with different numbers of processes. The order of outputs varied between runs, showing that process execution order is not fixed in MPI systems.

The program was then rewritten in a more functional style by breaking main() into smaller helper functions. This improved readability, maintainability, and testing.

Different send variants were tested:
- MPI_Send
- MPI_Ssend
- MPI_Bsend
- MPI_Rsend
- MPI_Isend

Internal timing was added around send and receive operations. The measured times were very small and somewhat inconsistent, which is expected because communication overhead is short and variance can be comparable to the timing itself.

## 3. Part 2: Latency and Bandwidth
A ping-pong program was implemented using MPI_Send and MPI_Recv between exactly two processes.

For latency testing, the same small message was sent back and forth many times. As the number of pings increased, the average time per ping should converge towards a stable value.

For bandwidth testing, the message was replaced with an array of doubles. The array size was varied from 8B to 2MiB. This data can be plotted and fitted with a straight line:
y = mx + c

Interpretation:
- c corresponds to latency
- m is related to inverse bandwidth

## 4. Part 3: Collective Communications
Several different versions of the vector-sum problem were implemented:
- DIY Send/Recv
- Broadcast + local processing + Reduce
- Scatter + Gather
- Scatter + Reduce
- Scatter + Custom Reduce

These were compared for speed and correctness.

Predictions:
- Broadcast should reduce repeated initialisation work
- Scatter should reduce memory duplication
- Reduce should be faster and cleaner than manual send/recv or gather-and-sum
- The built-in MPI reduce operation should be more reliable and probably faster than a custom one

## 5. Discussion
This activity showed that MPI communication patterns strongly affect performance and reliability. Point-to-point operations are flexible but can become verbose and harder to manage. Collective communications provide simpler and often more efficient alternatives.

Latency dominates very small messages, while bandwidth becomes the main limitation for larger messages. For vector operations, collective routines such as Scatter and Reduce are expected to outperform manual communication loops as process counts and data sizes grow.

## 6. Conclusion
Week 4 demonstrated how MPI communication behavior depends on both implementation choice and message size. Manual send/receive routines are useful for understanding MPI, but collective operations are generally cleaner and often more efficient. Ping-pong benchmarking provides a practical method for estimating latency and bandwidth in a distributed system.
