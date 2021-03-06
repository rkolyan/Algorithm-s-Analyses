import numpy as np
import matplotlib.pyplot as plot

def fill_array_of_results(filename):
    yarray = [];
    i = 1;
    tmp_file = open(filename, "r");
    for line in tmp_file:
        yarray.append(float(line));
        i += 1;
    tmp_file.close();
    return np.array(yarray);

def draw_graphic(xarray, yarrays):
    figure = plot.figure();
    plot.plot(xarray, yarrays[0], label = 'Стандартное умножение');
    plot.plot(xarray, yarrays[1], label = 'Умножение методом Винограда');
    plot.legend();
    plot.title('Графики скоростей алгоритмов');
    plot.ylabel('Процессорное время, тики');
    plot.xlabel('Длины сторон квадратных матриц');
    plot.grid(True);
    plot.show();

if __name__ == "__main__":
    yarrays = list();
    yarrays.append(fill_array_of_results("calculations/standard_multiply.txt"));
    yarrays.append(fill_array_of_results("calculations/vinograd_multiply.txt"));
    xarray = list();
    for i in range(len(yarrays[0])):
        xarray.append(i + 1);
    draw_graphic(np.array(xarray), yarrays);
