# Week 2 Report: Performance and Parallelism

## 1. Objective
The aim of this exercise was to investigate program performance using Linux timing tools, and to compare execution speed between C and Python for simple computational and file input/output tasks.

---

## 2. Methods

### External timing
The Linux `time` command was used to measure:
- **real** time (wall-clock time)
- **user** CPU time
- **sys** system (kernel) time

### Internal timing
- In **C**, timing was done using `clock()`
- In **Python**, timing was done using `time.time()`

These allow measurement of specific parts of code (e.g. loops or file operations).

---

## 3. Results and Observations

### 3.1 Hello World
- Python: ~0.033 s  
- C: ~0.004 s  

C is significantly faster due to no interpreter overhead.

---

### 3.2 Repeat Adder

- Runtime depends on number of loop iterations (second argument)
- C execution time ≈ 0.003–0.010 s
- Python execution time ≈ 0.028–0.079 s

Key observation:
> Performance depends more on algorithm structure than language alone.

---

### 3.3 Printing to Screen

C (1000 values): ~0.000165 s  
Python (1000 values): ~0.000666 s  

Printing time increases with output size.

---

### 3.4 File Writing

| Lines | C Time (s) | Python Time (s) |
|------|-----------|----------------|
| 100  | 0.000139  | 0.002388       |
| 1000 | 0.000174  | 0.003670       |
| 5000 | 0.000604  | 0.005803       |
| 10000| 0.001934  | 0.008456       |

C is consistently faster.

---

### 3.5 File Reading

| Lines | C Time (s) | Python Time (s) |
|------|-----------|----------------|
| 100  | 0.000048  | 0.001001       |
| 1000 | 0.000117  | 0.002005       |
| 5000 | 0.000391  | 0.003111       |
| 10000| 0.000824  | 0.004113       |

Reading is faster than writing in both languages.

---

### 3.6 Internal vs External Timing

Example (writing 10000 lines):

- Internal C: ~0.0018 s  
- External (`time`): ~0.009 s  

- Internal Python: ~0.0083 s  
- External (`time`): ~0.034 s  

Observation:
> External timing includes program startup overhead, while internal timing isolates the operation.

---

## 4. Discussion

- C is faster due to compilation and direct execution.
- Python has overhead from interpretation but is easier to write and modify.
- Performance is strongly influenced by:
  - Loop size
  - File operations
  - Output to screen
- Timing method matters:
  - External → whole program
  - Internal → specific code section

---

## 5. Conclusion

This exercise demonstrated that:
- C provides better raw performance, especially for loops and file I/O
- Python is slower but still efficient for many tasks
- Algorithm design has a larger impact than language choice
- Proper benchmarking requires understanding what exactly is being measured

