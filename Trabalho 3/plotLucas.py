# -*- coding: utf-8 -*-
"""
Created on Fri Jul 17 23:23:20 2020

@author: bruno
"""
from matplotlib import pyplot as plt
import numpy as np

threads = np.array([1, 2, 4, 8, 16])
pi_1 = np.array([3.141592652588050, 3.141592652589258, 3.141592652589210, 3.141592652589324, 3.141592652590205]) # Série de Leibniz
pi_2 = np.array([3.141592653589787, 3.141592653589787, 3.141592653589787, 3.141592653589787, 3.141592653589787]) # Série de Nilakantha
pi = np.array([3.141592653589793, 3.141592653589793, 3.141592653589793, 3.141592653589793, 3.141592653589793]) # Valor real
t_1 = np.array([5.141, 9.633, 11.356, 8.426, 5.980]) # Tempo da série de Leibniz
t_2 = np.array([7.424, 9.338, 9.597, 11.984, 7.427]) # Tempo da série de Euler

#plt.plot(threads, pi_1, label="Leibniz")
plt.plot(threads, pi_2, label="Nilakantha pi")
plt.plot(threads, pi_1, label="Leibniz pi")
plt.plot(threads, t_1, label="Leibniz t")
plt.plot(threads, t_2, label="Nilakantha t")
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
print(pi_1)