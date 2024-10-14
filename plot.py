import numpy as np
import matplotlib.pyplot as plt
import argparse

parser = argparse.ArgumentParser(description='Graficar los resultados de Q vs Media %CC.')
parser.add_argument('--file', type=str, required=True, help='Ruta al archivo de resultados')
parser.add_argument('--mask', action='store_true', help='Aplicar filtro a ciertos valores de N')
args = parser.parse_args()


file_path = args.file

with open(file_path, 'r') as file:
    lines = file.readlines()

N_values = []
Q_values = []
CC_values = []

for line in lines:
    parts = line.split()
    N = int(parts[1])
    Q = float(parts[3])
    CC = float(parts[6])
    
    N_values.append(N)
    Q_values.append(Q)
    CC_values.append(CC)

N_values = np.array(N_values)
Q_values = np.array(Q_values)
CC_values = np.array(CC_values)

unique_N = np.unique(N_values)

# Mask:
N_values_to_plot = [400, 2500, 4900]

# Graficar
plt.figure(figsize=(10, 6))

if args.mask:
    for N in N_values_to_plot:
        mask = N_values == N
        plt.plot(Q_values[mask], CC_values[mask], label=f'N = {N}', marker='o')
else:
    for N in unique_N:
        mask = N_values == N
        plt.plot(Q_values[mask], CC_values[mask], label=f'N = {N}', marker='o')

plt.xlabel('Q')
plt.ylabel('Media %CC')
plt.title('Gráfica de Q vs Media %CC para distintos valores de N')
plt.legend()
plt.grid(True)
plt.show()

