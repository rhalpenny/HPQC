# Week 5: Communicators and Topologies

## Overview
This activity investigates oscillations on a string in serial and MPI-parallel forms, and then extends the model to a more realistic spring-mass system.

## Files
- string_wave.c
- string_wave_flexible.c
- string_wave_mpi.c
- string_wave_springs.c
- animate_line.py
- animate_line_file.py
- animate_line_file_flexible.py

## Compilation
```bash
gcc HPQC/week5/string_wave_flexible.c -o bin/string_wave_flexible -lm
mpicc HPQC/week5/string_wave_mpi.c -o bin/string_wave_mpi -lm
gcc HPQC/week5/string_wave_springs.c -o bin/string_wave_springs -lm
