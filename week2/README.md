# Week 2 – Performance and Parallelism

## Overview
This activity explored different ways of measuring program runtime in Linux, and compared the performance of C and Python for simple tasks. The work included:

- using the Linux `time` command to measure full program runtime
- compiling and running C programs
- comparing C and Python versions of simple programs
- measuring file writing and file reading performance
- observing how runtime changes as input size increases

## Files Included
- `write_file.py` – writes a chosen number of lines to a file and reports runtime
- `read_file.py` – reads the written file into memory and reports runtime
- `write_file.c` – C version of the file writing program
- `read_file.c` – C version of the file reading program

## How to Run

### Python programs
Run the Python write program with a chosen number of lines:

```bash
python3 write_file.py 1000
