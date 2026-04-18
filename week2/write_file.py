import sys
import time
import os

if len(sys.argv) != 2:
    print("Usage: python3 write_file.py <number_of_lines>")
    sys.exit(1)

n = int(sys.argv[1])
filename = os.path.expanduser("~/data/week2/output.txt")

start_time = time.time()

with open(filename, "w") as f:
    for i in range(n):
        f.write(f"This is line {i}\n")

end_time = time.time()

run_time = end_time - start_time

print(f"Wrote {n} lines to {filename}")
print(f"Runtime: {run_time:.6f} seconds")
