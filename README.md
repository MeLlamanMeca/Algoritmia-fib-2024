# Percolation connection threshold

Este proyecto implementa un algoritmo para calcular el umbral de conexión de percolación en grafos. Permite analizar cómo se conectan diferentes componentes en un grafo y visualizar los resultados.

## Requisitos

Asegúrate de tener instalados los siguientes programas y bibliotecas:

- **Compilador C++**:
  - `g++`: Necesario para compilar el código C++. Puedes instalarlo a través de tu gestor de paquetes.
  
- **Python**:
  - `Python 3.x`: Asegúrate de tener Python instalado. Puedes descargarlo desde [python.org](https://www.python.org/downloads/).

- **Bibliotecas de Python**:
    - `numpy`: Para la manipulación de datos. Puedes instalarlo usando pip:
    ```bash
    pip install numpy
    ```
    - `matplotlib`: Para la visualización de gráficas. Puedes instalarlo usando pip:
    ```bash
    pip install matplotlib
    ```
    - `argparse`: Esta biblioteca es parte de la biblioteca estándar de Python, por lo que no es necesario instalarla por separado.


## Compilación

Para compilar el proyecto, utiliza el siguiente comando:

```bash
    make
```

Para descompilar:

```bash
    make clean
```

## Ejecución

Una vez compilado, puedes ejecutar el programa con el siguiente comando:
```bash
    ./main.exe [graphType] (percolationType) ([N inicial] [N final] [Salto de N] [P inicial] [Numero de saltos] [Salto de P] [Muestras])
    [graphType]: -info | -nxn | -rgg | -trg
    (percolationType): -node | -edge (DEFAULT)
    [compulsory] (optional)
```

## Visualización de gráficas

Para dibujar gráficas de los resultados, utiliza el script de Python ```plot.py```. El comando para ejecutar el script es el siguiente:
```bash
    python plot.py [-h] --file FILE [--mask] [--mean] [--limit] [--clear]
```