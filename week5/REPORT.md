# Week 5 Report: Communicators and Topologies

## 1. Objective
The goal of this activity was to investigate a simple oscillating-string model in serial form, remove hard-coded values, implement an MPI-based parallel version, and then improve the physical realism of the model using a spring-mass system.

## 2. Part 1: Serial Code
The original serial string-wave model was examined as a starting point. The purpose of the model was to simulate oscillations on a string and write the values to a CSV file so that they could be visualised later using a Python animation script.

A modified serial version of the program was then created to remove hard-coded values. The improved version allows the user to specify:
- number of points
- number of cycles
- sampling interval
- output file path

This made the code more flexible and easier to document and reuse.

The animation script was also modified so that:
- the input CSV file can be chosen on the command line
- the output GIF file can be chosen on the command line
- the frame interval can be controlled by the user

This improved the usability of the plotting code and removed dependence on hard-coded file names.

## 3. Part 2: Parallelisation Strategy
The string was divided into chunks along its length so that each MPI process handled one local section of the string.

Some operations are naturally parallel:
- updating the values inside each local chunk
- storing temporary values for each local section

Other operations require communication:
- exchanging boundary values between neighbouring chunks
- gathering all local chunks into a single array before writing output

To ensure safe file output, only the root process wrote the CSV file. Each worker process computed its local chunk, and then the data was gathered in memory using MPI before being written by the root process. This avoided the unsafe situation where several processes attempt to write to the same file simultaneously.

## 4. Benchmarking Results

### 4.1 Flexible serial benchmark
A dedicated single benchmark run for the flexible serial version failed with:

`-bash: ./bin/string_wave_flexible: No such file or directory`

So that individual timing could not be used directly. However, the scaling benchmark results below provide valid serial timing data for the same program.

### 4.2 Serial scaling
Measured serial timings were:

- 1000 points:
  - real = 0.026 s
  - user = 0.014 s
  - sys = 0.005 s

- 10000 points:
  - real = 0.125 s
  - user = 0.081 s
  - sys = 0.008 s

- 100000 points:
  - real = 1.140 s
  - user = 0.767 s
  - sys = 0.045 s

This shows that runtime increases significantly as the problem size increases, which is expected for a larger simulation.

### 4.3 MPI benchmark
A standalone MPI benchmark run produced:

- real = 0.438 s
- user = 0.151 s
- sys = 0.170 s

The message `No protocol specified` also appeared during MPI runs. Since the job still completed and timing output was produced, this appears to be related to the runtime environment rather than a complete program failure.

### 4.4 MPI scaling with 2 processes
Measured timings were:

- 1000 points:
  - real = 0.447 s
  - user = 0.141 s
  - sys = 0.077 s

- 10000 points:
  - real = 0.509 s
  - user = 0.248 s
  - sys = 0.116 s

- 100000 points:
  - real = 1.612 s
  - user = 1.784 s
  - sys = 0.179 s

### 4.5 MPI scaling with 4 processes
Measured timings were:

- 1000 points:
  - real = 0.440 s
  - user = 0.163 s
  - sys = 0.180 s

- 10000 points:
  - real = 0.574 s
  - user = 0.601 s
  - sys = 0.174 s

- 100000 points:
  - real = 1.660 s
  - user = 3.549 s
  - sys = 0.237 s

### 4.6 Comparison of serial and parallel performance
Comparing serial and MPI results:

#### For 1000 points
- Serial: 0.026 s
- MPI (2 processes): 0.447 s
- MPI (4 processes): 0.440 s

Serial is much faster.

#### For 10000 points
- Serial: 0.125 s
- MPI (2 processes): 0.509 s
- MPI (4 processes): 0.574 s

Serial is still clearly faster.

#### For 100000 points
- Serial: 1.140 s
- MPI (2 processes): 1.612 s
- MPI (4 processes): 1.660 s

Serial remains faster, although the gap is smaller than at lower input sizes.

### 4.7 Interpretation
For the problem sizes tested here, the MPI version was not faster than the serial version. This suggests that the communication and gathering overhead outweighed the benefit of parallelism at these scales.

This means:
- the parallel solution is functional
- but the problem does not strongly demand parallelisation at the tested sizes
- a parallel solution may only become worthwhile at larger scales, or with a more computationally expensive update rule

Also, for MPI runs the sum of user and sys time exceeded real time in the larger runs, which is consistent with parallel work being carried out across multiple processes.

## 5. Animation and Functional Testing
The following animations were successfully generated:
- `string_wave_flexible.gif`
- `string_wave_mpi.gif`
- `string_wave_springs.gif`

This confirms that all three programs produced CSV outputs in the expected format, and that the plotting script could read and animate those files successfully.

Since the GIF files were saved without error, the output structure appears to be valid. Visual inspection is still important, but successful animation strongly suggests that the data format and simulation pipeline were functional.

## 6. Part 3: Improved Physics Model
The original update rule in the basic string model was not especially realistic, because each point effectively copied a neighbouring value in a very simple way. To improve the physical realism of the system, a spring-mass model was implemented.

The improved model introduced:
- position
- velocity
- acceleration
- spring constant `k`
- mass `m`
- time step `dt`

Each point was treated as though attached to its neighbours by springs, and the total force on each point was calculated using Hooke’s law. This force was used to determine acceleration, then velocity, then updated position.

The benchmark for the improved model gave:

- real = 0.013 s
- user = 0.007 s
- sys = 0.003 s

This shows that the model ran efficiently for the chosen parameters. The main value of this part was not raw speed, but the improvement in physical realism.

## 7. Discussion
Week 5 highlighted several important ideas.

First, hard-coded programs are difficult to reuse and test. By allowing command line arguments to control simulation parameters and output paths, the code became far more flexible and easier to document.

Second, not all problems benefit immediately from parallelisation. Although the MPI version worked and produced output that could be animated, the serial code remained faster for all tested input sizes. This shows that MPI communication overhead is significant, especially when the update rule is relatively simple.

Third, improving the physics of a model may matter more than simply parallelising it. The spring-mass version provides a more realistic interpretation of the motion of a string, and therefore improves the scientific value of the simulation even if it is still relatively simple.

Finally, the aggregation strategy was important. Gathering results in memory and writing only on the root process was a safe and sensible design choice, because it avoided file corruption and race conditions.

## 8. Conclusion
This activity showed how a simple serial simulation can be made more flexible, parallelised with MPI, and then extended into a more realistic physical model.

The MPI solution was functional, but for the tested problem sizes it was not faster than the serial version. This indicates that parallelisation is only worthwhile when the workload is large enough to overcome communication costs.

The improved spring-mass system provided a better physical model of string oscillation and demonstrated how the code can be extended beyond the original simplistic update rule.

Overall, Week 5 showed that good simulation work involves not only making code faster, but also making it more flexible, safer, and more physically meaningful.
