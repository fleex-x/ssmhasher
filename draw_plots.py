import matplotlib.pyplot as plt
import numpy as np
import json
import random
import sys
from scipy.interpolate import make_interp_spline
import math

def round50(x):
    return int(round(x / 50.0)) * 50

def print_plots(data, title, approximated):
    plt.grid()
    plt.xlabel('number of bytes')
    plt.ylabel('time (ns)')
    for ind, hash_function in enumerate(data):
        # if hash_function == "murMurHash3_32":
        #     continue
        xs = np.array([point[0] for point in data[hash_function]])
        ys = np.array([point[1] for point in data[hash_function]])

        if approximated:
            x_y_spline = make_interp_spline(xs, ys)
            x_min = min(xs)
            x_max = max(xs)
            approximated_xs = np.linspace(int(x_min), int(x_max), 500)
            approximated_ys = x_y_spline(approximated_xs)
            xs = approximated_xs
            ys = approximated_ys

        plt.plot(xs, ys, label=hash_function)
        # if ind >= 2:
        #     break

    axes = plt.gca()
    y_min, y_max = axes.get_ylim()
    x_min, x_max = axes.get_xlim()
    plt.xticks(np.arange(round50(x_min), round50(x_max), 50.0))
    plt.yticks(np.arange(round50(y_min), round50(y_max), 50.0))

    plt.title(title)
    plt.legend()
    # plt.savefig('graphics/'title + '.png')

def print_plots_from_file(file, approximated):
    with open(file) as chart1:
        data = json.load(chart1)
        print_plots(data, file[:-5], approximated)

for file in sys.argv[1:]:
    print_plots_from_file(file, True)
