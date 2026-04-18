"""
Animate a string-wave CSV file and save it as a GIF.

Usage:
    python3 animate_line_file_flexible.py <input_csv> <output_gif> <interval_ms>
"""

import sys
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

def check_args():
    if len(sys.argv) != 4:
        raise Exception(
            "Usage: python3 animate_line_file_flexible.py <input_csv> <output_gif> <interval_ms>\n"
            "Example: python3 animate_line_file_flexible.py data/week5/string_wave_flexible.csv data/week5/string_wave_flexible.gif 50"
        )

def main():
    check_args()

    input_csv = sys.argv[1]
    output_gif = sys.argv[2]
    interval_ms = int(sys.argv[3])

    df = pd.read_csv(input_csv)
    cycles = sorted(df["cycle"].unique())

    fig, ax = plt.subplots()
    line, = ax.plot([], [], lw=2)

    x_vals = sorted(df["point"].unique())
    y_min = df["value"].min()
    y_max = df["value"].max()

    ax.set_xlim(min(x_vals), max(x_vals))
    ax.set_ylim(y_min - 0.1, y_max + 0.1)
    ax.set_xlabel("Point")
    ax.set_ylabel("Value")
    ax.set_title("String Oscillation")

    def update(frame):
        sub = df[df["cycle"] == frame]
        line.set_data(sub["point"], sub["value"])
        ax.set_title(f"String Oscillation - Cycle {frame}")
        return line,

    ani = FuncAnimation(fig, update, frames=cycles, interval=interval_ms, blit=True)
    ani.save(output_gif, writer=PillowWriter(fps=max(1, 1000 // interval_ms)))
    print(f"Saved animation to {output_gif}")

if __name__ == "__main__":
    main()
