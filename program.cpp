#include <iostream>
#include "grafoNxN.cpp"
using namespace std;



/*  
    Este main se encarga de procesar y generar todos los grafos 
    almacenando sus datos para su posterior analisis 
*/

int main() {
    // Estudiamos cada valor de n por separado
    /*
    for (int n = 20; n <= 10000; n += 10) {
        grafoNxN g(n);   // Generador de grano nxn base
        for (double q = 0.0; q <= 1.0; q += 0.05) {
            for (int muestra = 1; muestra <= 100; ++muestra) {
                //grafoNxN grafo_aleatorio = g.percolación tipo nodo o vértice
            }
        }
    }
    */

    grafoNxN g(3);
    g.printGraph();
    grafoNxN copia = g;
    copia.edgePercolation(0.5);
    copia.printGraph();
    grafoNxN copia2 = g;
    copia2.nodePercolation(0.5);
    copia2.printGraph();
}
