import numpy as np
import matplotlib.pyplot as plot

def fill_array_of_results(filename):
    yarray = [0];
    i = 1;
    tmp_file = open(filename, "r");
    for line in tmp_file:
        yarray.append(int(line));
        i += 1;
    tmp_file.close();
    return np.array(yarray);

def draw_graphic(xarrays, yarrays):
    figure = plot.figure();
    plot.plot(xarrays[0], yarrays[0], label = 'Damerlau-Levenstein');
    plot.plot(xarrays[0], yarrays[1], label = 'Levenstein');
    plot.plot(xarrays[0], yarrays[2], label = 'Damerlau-Levenstein Memory Modified');
    plot.plot(xarrays[0], yarrays[3], label = 'Levenstein Memory Modified');
    plot.plot(xarrays[1], yarrays[4], label = 'Levenstein Recursive');
    plot.legend();
    #plot.legend((line1, line2), (u'Damerlau-Levenstein', u'Levenstein'), loc='upper left');
    plot.title('Graphics of algorithm\'s speed');
    plot.ylabel('Process Time, clocks');
    plot.xlabel('Element\'s count');
    plot.grid(True);
    plot.show();

if __name__ == "__main__":
    yarrays = list();
    yarrays.append(fill_array_of_results("calculations/damerlau_levenstein_matrix_sum_results.txt"));
    yarrays.append(fill_array_of_results("calculations/levenstein_matrix_sum_results.txt"));
    yarrays.append(fill_array_of_results("calculations/damerlau_levenstein_results.txt"));
    yarrays.append(fill_array_of_results("calculations/levenstein_results.txt"));
    yarrays.append(fill_array_of_results("calculations/recursive_levenstein_results.txt"));
    xarrays = list();
    xarray = [0]
    for i in range(len(yarrays[0]) - 1):
        xarray.append(i + 1);
    xarrays.append(np.array(xarray));
    xarray = [0];
    for i in range(len(yarrays[4]) - 1):
        xarray.append(i + 1);
    xarrays.append(np.array(xarray));
    draw_graphic(xarrays, yarrays);
