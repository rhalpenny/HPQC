# Week 2: Performance and Parallelism

## Overview
This activity investigates different ways of measuring runtime in Linux, C and Python. The work includes benchmarking with the Linux `time` command, comparing C and Python versions of simple programs, measuring internal runtime using timing functions inside programs, and testing file input/output performance in both C and Python.

## Files in this directory
- `hello_world.c` and `hello_world.py` - simple hello world programs
- `repeat_adder.c` and `repeat_adder.py` - multiplication by repeated addition
- `time_print.c` and `time_print.py` - programs that internally time output to screen
- `time_file_write.c` - writes lines to a file and measures runtime
- `time_file_read.c` - reads a file into memory and measures runtime
- `time_file_write.py` - Python version of file writing benchmark
- `time_file_read.py` - Python version of file reading benchmark

## Compilation
The C programs were compiled from the home directory using:

```bash
gcc HPQC/week2/hello_world.c -o bin/hello_world
gcc HPQC/week2/repeat_adder.c -o bin/repeat_adder
gcc HPQC/week2/time_print.c -o bin/time_print
gcc HPQC/week2/time_file_write.c -o bin/time_file_write
gcc HPQC/week2/time_file_read.c -o bin/time_file_read
