import numpy as np
import matplotlib.pyplot as plot

def fill_array_of_results(filename):
    yarray = [0];
    i = 1;
    tmp_file = open(filename, "r");
    for line in tmp_file:
        yarray.append(float(line));
        i += 1;
    tmp_file.close();
    return np.array(yarray);

def draw_graphic(xarray, yarrays):
    figure = plot.figure();
    plot.plot(xarray, yarrays[0], label = 'Standard Muptiply');
    plot.plot(xarray, yarrays[1], label = 'Standard Muptiply Optimized');
    plot.plot(xarray, yarrays[2], label = 'Vinograd Multiply');
    plot.plot(xarray, yarrays[3], label = 'Vinograd Muptiply Optimized');
    plot.plot(xarray, yarrays[4], label = 'Vinograd Muptiply Optimized 2');
    plot.legend();
    plot.title('Graphics of speed of algorithms');
    plot.ylabel('Process time, clocks');
    plot.xlabel('Matrix side length');
    plot.grid(True);
    plot.show();

if __name__ == "__main__":
    yarrays = list();
    yarrays.append(fill_array_of_results("calculations/standard_multiply.txt"));
    yarrays.append(fill_array_of_results("calculations/standard_multiply_optimized.txt"));
    yarrays.append(fill_array_of_results("calculations/vinograd_multiply.txt"));
    yarrays.append(fill_array_of_results("calculations/vinograd_multiply_optimized1.txt"));
    yarrays.append(fill_array_of_results("calculations/vinograd_multiply_optimized2.txt"));
    xarray = [0];
    for i in range(len(yarrays[0]) - 1):
        xarray.append(i + 1);
    draw_graphic(np.array(xarray), yarrays);
