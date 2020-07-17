from matplotlib import pyplot as plt
import numpy as np

data = []

with open("ResultadosMeuPc.txt","r") as f:
    for line in f:
        data.append(line.split())
        
arrThreads = np.array([1, 2, 4, 8 ,16])

timeLGM = []
timeNila = []

for line in data:
    if line[0] == 'LGM':
        timeLGM.append(float(line[2]))
    elif line[0] == 'NIL':
        timeNila.append(float(line[2]))

timeLGM = np.array(timeLGM)
timeNila = np.array(timeNila)

plt.plot(arrThreads, timeLGM, label="L. G. M.")
plt.plot(arrThreads, timeNila, label="Nilakantha")
plt.title("Relação entre o número de threads e o tempo \n "
          "necessário para calcular pi através de séries iterativas")
plt.ylabel('Tempo (s)')
plt.xlabel('Númer de Threads')
plt.grid()
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
plt.show()