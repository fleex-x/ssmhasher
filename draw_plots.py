#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np
import json
import random
import sys
from scipy.interpolate import make_interp_spline
import math

step = 50.0

def round_step(x):
    return int(round(x / step)) * step

def print_plots(data, title, approximated):
    plt.grid()
    plt.xlabel('number of bytes')
    plt.ylabel('time (ns)')
    for hash_function in data:
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

    axes = plt.gca()
    y_min, y_max = axes.get_ylim()
    x_min, x_max = axes.get_xlim()
    plt.xticks(np.arange(round_step(x_min), round_step(x_max), step))
    plt.yticks(np.arange(round_step(y_min), round_step(y_max), step))

    plt.title(title)
    plt.legend()
    plt.show()
    # plt.savefig('graphics/' + title + '.png')

def print_plots_from_file(file, approximated):
    with open(file) as chart1:
        data = json.load(chart1)
        print_plots(data, file[7:-5], approximated)

step = float(sys.argv[1])

for file in sys.argv[2:]:
    print_plots_from_file(file, True)
