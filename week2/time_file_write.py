import sys
import time

if len(sys.argv) != 3:
    print(f"Usage: python3 {sys.argv[0]} <number_of_lines> <output_file>")
    sys.exit(1)

n = int(sys.argv[1])
filename = sys.argv[2]

start_time = time.time()

with open(filename, "w") as f:
    for i in range(n):
        f.write(f"This is line {i}\n")

end_time = time.time()
run_time = end_time - start_time

print(f"Wrote {n} lines to {filename} in {run_time:.6f} seconds")
