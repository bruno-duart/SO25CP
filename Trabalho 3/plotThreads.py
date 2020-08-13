from matplotlib import pyplot as plt
import numpy as np

data = []

with open("ResultadosMeuPc.txt","r") as f:
    for line in f:
        data.append(line.split())
        
arrThreads = np.array([1, 2, 4, 8 ,16])

timeLGM = []
timeNila = []
piLGM = []
piNila = []

for line in data:
    if line[0] == 'LGM':
        timeLGM.append(float(line[2]))
        piLGM.append(float(line[4]))
    elif line[0] == 'NIL':
        timeNila.append(float(line[2]))
        piNila.append(float(line[4]))

timeLGM = np.array(timeLGM)
timeNila = np.array(timeNila)
piLGM = np.array(piLGM)
piNila = np.array(piNila)
pi = np.array([np.pi, np.pi, np.pi, np.pi, np.pi])

piLGMmedia = 0
for val in piLGM:
    piLGMmedia += val
piLGMmedia /= 5

piNilamedia = 0
for val in piNila:
    piNilamedia += val
piNilamedia /= 5

exatidLGM = (piLGMmedia - np.pi)
exatidNila = (piNilamedia - np.pi)
print(np.pi)
plt.plot(arrThreads, timeLGM, label="L. G. M.")
plt.plot(arrThreads, timeNila, label="Nilakantha")
plt.title("Relação entre o número de threads e o tempo \n "
          "necessário para calcular pi através de séries iterativas")
plt.ylabel('Tempo (s)')
plt.xlabel('Número de Threads (N)')
plt.grid()
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
#plt.savefig("Figure_1.pdf", format="pdf", bbox_inches="tight")
# plt.show()

# plt.plot(arrThreads, piLGM, label="L. G. M.")
# plt.plot(arrThreads, piNila, label="Nilakantha")
# plt.plot(arrThreads, pi, label="PI")
# plt.title("Comparação entre os valores obtidos para PI por cada série \n "
#           "em relação ao número de threads")
# plt.ylabel('Tempo (s)')
# plt.xlabel('Númer de Threads')
# plt.grid()
# plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)