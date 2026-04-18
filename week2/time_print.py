import sys
import time

def main():
    try:
        in_arg = int(sys.argv[1])
    except:
        raise Exception("Incorrect arguments.\nUsage: python3 time_print.py [NUM]\ne.g.\npython3 time_print.py 23")

    start_time = time.time()

    for i in range(in_arg):
        print("{}, ".format(i), end="")

    end_time = time.time()
    run_time = end_time - start_time

    print("\n\nTime for loop: {} seconds\n".format(run_time))

if __name__ == "__main__":
    main()
