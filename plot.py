import argparse
import numpy as np
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(description='Graficar los resultados de Q vs Media %CC.')
parser.add_argument('--file', type=str, required=True, help='Ruta al archivo de resultados')
parser.add_argument('--mask', action='store_true', help='Aplicar filtro a ciertos valores de N')
parser.add_argument('--mean', action='store_true', help='Graficar la media de todas las curvas')
parser.add_argument('--limit', action='store_true', help='Graficar la curva límite conforme N aumenta')
parser.add_argument('--clear', action='store_true', help='No muestra ninguna curva salvo las limit y mean')
args = parser.parse_args()

file_path = args.file

# Try utf-8 or latin-1
try:
    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()
except UnicodeDecodeError:
    with open(file_path, 'r', encoding='latin-1') as file:
        lines = file.readlines()

N_values = []
Q_values = []
CC_values = []

for line in lines:
    clean_line = line.replace('\x00', '').strip()
    if clean_line:
        parts = clean_line.split()
        if len(parts) >= 7:
            try:
                N = int(parts[1])
                Q = float(parts[3])
                CC = float(parts[6])
                
                N_values.append(N)
                Q_values.append(Q)
                CC_values.append(CC)
            except ValueError:
                print(f"Error al convertir valores en la línea: {clean_line}")

N_values = np.array(N_values)
Q_values = np.array(Q_values)
CC_values = np.array(CC_values)

unique_N = np.unique(N_values)

# Graficar
plt.figure(figsize=(10, 6))

# Graficar curvas individuales según el flag --mask
if args.mask:
    min_N = np.min(unique_N)
    max_N = np.max(unique_N)
    median_N = np.median(unique_N)

    median_N = unique_N[np.abs(unique_N - median_N).argmin()]

    N_values_to_plot = [min_N, median_N, max_N]
    
    plt.plot(Q_values[N_values == min_N], CC_values[N_values == min_N], label=f'N = {min_N}, mínimo', marker='o')
    plt.plot(Q_values[N_values == median_N], CC_values[N_values == median_N], label=f'N = {median_N}, mediana', marker='o')
    plt.plot(Q_values[N_values == max_N], CC_values[N_values == max_N], label=f'N = {max_N}, máximo', marker='o')
elif not args.clear:
    for N in unique_N:
        mask = N_values == N
        plt.plot(Q_values[mask], CC_values[mask], marker='o')

# Flag --mean: graficar la curva promedio de todas las curvas
if args.mean:
    unique_Q = np.unique(Q_values)
    mean_CC = []
    
    for q in unique_Q:
        mask = Q_values == q
        mean_CC.append(np.mean(CC_values[mask]))
    
    plt.plot(unique_Q, mean_CC, label='Media de todas las curvas', marker='x', color='black', linestyle='--')

# Flag --limit:
if args.limit:
    N_max = np.max(N_values)
    mask = N_values == N_max
    plt.plot(Q_values[mask], CC_values[mask], label=f'Límite (N = {N_max})', marker='s', color='red', linestyle='-.')


plt.xlabel('Q')
plt.ylabel('Media %CC')
plt.title('Gráfica de Q vs Media %CC para distintos valores de N')
plt.legend()
plt.grid(True)
plt.show()