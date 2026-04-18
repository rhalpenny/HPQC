import time
import os

filename = os.path.expanduser("~/data/week2/output.txt")

start_time = time.time()

with open(filename, "r") as f:
    data = f.readlines()

end_time = time.time()

run_time = end_time - start_time

print(f"Read {len(data)} lines from {filename}")
print(f"Runtime: {run_time:.6f} seconds")
