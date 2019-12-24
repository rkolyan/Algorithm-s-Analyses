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
    plot.plot(xarray, yarrays[0], label = 'Стандартный алгоритм');
    plot.plot(xarray, yarrays[1], label = 'Алгоритм Винограда');
    plot.legend();
    #plot.title('График зависимости проц. времени работы от размера кв. матриц');
    plot.ylabel('Процессорное время, тики');
    plot.xlabel('Длина стороны квадратной матрицы, кол-во элементов');
    plot.grid(True);
    plot.show();

if __name__ == "__main__":
    yarrays = list();
    yarrays.append(fill_array_of_results("calculations/standard_multiply.txt"));
    yarrays.append(fill_array_of_results("calculations/vinograd_multiply.txt"));
    xarray = [];
    for i in range(100, 1002, 100):
        xarray.append(i);
        xarray.append(i + 1);
    draw_graphic(np.array(xarray), yarrays);
