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

def draw_graphic(xarray, yarrays, message):
    figure = plot.figure();
    plot.plot(xarray, yarrays[0], label = 'Сортировка минимум/максимум');
    plot.plot(xarray, yarrays[1], label = 'Сортировка пузырьком');
    plot.plot(xarray, yarrays[2], label = 'Сортировка шейкером');
    plot.legend();
    plot.title('Скорость работы алгоритма ' + message);
    plot.ylabel('Процессорное время, тики');
    plot.xlabel('Длина массива, количество элементов');
    plot.grid(True);
    plot.show();

if __name__ == "__main__":
    yarrays = list();
    yarrays.append(fill_array_of_results("calculations/sort_min_max_random.txt"));
    yarrays.append(fill_array_of_results("calculations/sort_bubble_random.txt"));
    yarrays.append(fill_array_of_results("calculations/sort_shaker_random.txt"));
    yarrays.append(fill_array_of_results("calculations/sort_min_max_sorted.txt"));
    yarrays.append(fill_array_of_results("calculations/sort_bubble_sorted.txt"));
    yarrays.append(fill_array_of_results("calculations/sort_shaker_sorted.txt"));
    yarrays.append(fill_array_of_results("calculations/sort_min_max_unsorted.txt"));
    yarrays.append(fill_array_of_results("calculations/sort_bubble_unsorted.txt"));
    yarrays.append(fill_array_of_results("calculations/sort_shaker_unsorted.txt"));
    xarray = [0];
    for i in range(len(yarrays[0]) - 1):
        xarray.append(i + 1);
    draw_graphic(np.array(xarray), yarrays, '(случайный массив)');
    draw_graphic(np.array(xarray), yarrays[3:], '(отсортированный по возрастанию массив)');
    draw_graphic(np.array(xarray), yarrays[6:], '(отсортированный по убыванию массив)');
