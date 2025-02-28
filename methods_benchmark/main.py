import matplotlib.pyplot as plt
import math
import os
os.chdir("/home/maxim/study/4sem/Lorenz Attractor/methods_benchmark/methods_results")

integration_step  = [0.1, 0.05, 0.01, 0.005, 0.001, 0.0001]

euler = ["euler_" + str(step) for step in integration_step]
heun = ["heun_" + str(step) for step in integration_step]
rk4 = ["rk4_" + str(step) for step in integration_step]
trap = ["trap_" + str(step) for step in integration_step]

euler_results = []
heun_results = []
rk4_results = []
trap_results = []

def read_files(file_names, data_array):
    for file_name in file_names:
        f = open(file_name, "r")
        cur_data = []
        for line in f:
            cur_data.append(tuple(float(i) for i in line.rstrip("\n").split()))
        data_array.append(cur_data)

def reading_data():
    read_files(euler, euler_results)
    read_files(heun, heun_results)
    read_files(rk4, rk4_results)
    read_files(trap, trap_results)

def l2_mes(vec):
    return math.sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2])

def data_preprocessing(data):
    for i in range(len(data)):
        for j in range(len(data[i])):
            data[i][j] = l2_mes(data[i][j]) * 10

def ploting_data(data):
    for i in range(len(data)):
        plt.plot(data[i], label=f"{integration_step[i]}")
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.show()

def cross_plot(data1, data2, data3, data4, i):
    plt.plot(data1, label=f"euler {integration_step[i]}")
    plt.plot(data2, label=f"heun {integration_step[i]}")
    plt.plot(data3, label=f"rk4 {integration_step[i]}")
    plt.plot(data4, label=f"trap {integration_step[i]}")
    # plt.xscale('log')
    plt.yscale('log')
    plt.legend()
    plt.show()
    
def main():
    reading_data()
    data_preprocessing(euler_results)
    data_preprocessing(heun_results)
    data_preprocessing(rk4_results)
    data_preprocessing(trap_results)
    
    # ploting_data(trap_results)
    cross_plot(euler_results[3], heun_results[3], rk4_results[3], trap_results[3], 3)
    

if __name__ == "__main__":
    main()