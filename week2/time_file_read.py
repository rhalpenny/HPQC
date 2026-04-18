import sys
import time

if len(sys.argv) != 2:
    print(f"Usage: python3 {sys.argv[0]} <input_file>")
    sys.exit(1)

filename = sys.argv[1]

start_time = time.time()

with open(filename, "r") as f:
    lines = f.readlines()

end_time = time.time()
run_time = end_time - start_time

print(f"Read {len(lines)} lines from {filename} in {run_time:.6f} seconds")
