import numpy as np
import matplotlib.pyplot as plot

def fill_array_of_results(filename):
    yarray = [];
    tmp_file = open(filename, "r");
    for line in tmp_file:
        yarray.append(float(line));
    tmp_file.close();
    return np.array(yarray);

def draw_graphic(xarray, yarrays):
    figure = plot.figure();
    plot.plot(xarray, yarrays[0], label = 'Стандартный алгоритм');
    plot.plot(xarray, yarrays[1], label = 'Алгоритм Винограда');
    plot.legend();
    plot.title('Время умножения матриц размерностями 1001x1001');
    plot.ylabel('Реальное время, секунды');
    plot.xlabel('Количество потоков');
    plot.grid(True);
    plot.show();

if __name__ == "__main__":
    yarrays = list();
    yarrays.append(fill_array_of_results("result1001s.txt"));
    yarrays.append(fill_array_of_results("result1001v.txt"));
    xarray = [];
    for i in range(1, len(yarrays[0]) + 1):
        xarray.append(i);
    draw_graphic(np.array(xarray), yarrays);
