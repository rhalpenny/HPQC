# Week 5 Report: Communicators and Topologies

## 1. Objective
The goal of this activity was to investigate a simple oscillating-string model in serial form, remove hard-coded values, implement an MPI-based parallel version, and then improve the physical realism of the model using a spring-mass system.

## 2. Part 1: Serial Code
The original serial string-wave code was compiled and run successfully. It produced a CSV file that could be passed to the animation script to generate a visualisation of the oscillation.

The program was then modified to remove hard-coded values. The improved version allows the user to specify:
- number of points
- number of cycles
- sampling interval
- output file path

This made the code more flexible and easier to document and reuse.

The Python animation program was also modified so that both input and output file names, as well as frame timing, could be specified on the command line.

## 3. Part 2: Parallelisation Strategy
The string was split into chunks along its length. Each MPI process handled one local chunk of the string. Since neighboring points influence each other, boundary values had to be exchanged between neighboring processes at each update step.

Aggregation strategy:
- each process computed its local values
- root gathered the chunks into memory using MPI_Gather
- only the root process wrote the CSV file

This avoided unsafe simultaneous writes from multiple processes.

## 4. Testing and Benchmarking
The serial and MPI versions were benchmarked for increasing problem sizes. The purpose was to determine:
- whether the parallel solution is functionally correct
- whether a parallel solution is worthwhile
- at what scale, if any, MPI becomes viable

The generated CSV files were also passed to the animation program to check whether the oscillations looked sensible.

## 5. Part 3: Improved Physics Model
The basic update rule in the original model was not physically realistic. To improve the model, a spring-mass system was implemented with:
- position
- velocity
- acceleration
- spring constant k
- mass m
- timestep dt

Each interior point was treated as though connected to neighbors by springs, and the net spring force was used to update acceleration, then velocity, then position.

This produced a more realistic oscillatory system than the basic copy/shift update rule.

## 6. Discussion
The original string model is easy to understand and produces a very clean waveform, but it is not physically realistic. The spring-mass model is more complex but better represents actual oscillatory behavior.

The MPI implementation should become more useful as the number of points grows. For small problem sizes, communication and gathering overhead may dominate, making the serial code faster overall. For larger problem sizes, the parallel version may become viable if computation outweighs communication cost.

The choice of aggregation strategy is important because file writing must be handled safely. Gathering to root and writing once is reliable, though it can become a bottleneck for very large outputs.

## 7. Conclusion
Week 5 showed how a serial physical simulation can be made more flexible, parallelised with MPI, and then extended to a more realistic physical model. The activity also highlighted that parallelisation is only worthwhile when the problem size is large enough to justify the communication overhead.

Further refinement could include more advanced boundary conditions, a different communicator topology, or a fully parallelised spring-mass system.
