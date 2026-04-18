import sys

def main():
    try:
        a = int(sys.argv[1])
        b = int(sys.argv[2])
    except:
        raise Exception("Incorrect arguments.\nUsage: python3 repeat_adder.py [NUM1] [NUM2]\ne.g.\npython3 repeat_adder.py 4 5")

    total = 0
    for _ in range(b):
        total += a

    print(total)

if __name__ == "__main__":
    main()
