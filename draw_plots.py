import matplotlib.pyplot as matlb
import numpy as np
import cmath
import json
import random

def print_plots(data):
    matlb.grid()
    for hash_function in data:
        x_points = [point[0] for point in data[hash_function]]
        y_points = [point[1] for point in data[hash_function]]
        matlb.plot(x_points, y_points, label=hash_function)
    matlb.title('chart1')
    matlb.legend()
    matlb.show()

def print_plots_from_file(file):
    with open(file) as chart1:
        data = json.load(chart1)
        print_plots(data)
