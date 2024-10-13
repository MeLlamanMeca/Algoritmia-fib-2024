#include <iostream>
#include <vector>
#include <set>
#include <ciso646>
#include "Graph.cpp"
using namespace std;

class GraphTrg : public Graph {

public:
    GraphTrg() : Graph() { //Constructor por defecto
        GraphTrg(0);
    }
    
    GraphTrg(int n) : Graph() { //Constructor
        this->n = (n*(n+1))/2;
        exist.resize(this->n, true);
        adyacencias = vector<set<int>>(this->n);

        int nodo = 0;

        for (int i = 1; i <= n; ++i) {   //Por cada nivel
            for (int j = 1; j <= i; ++j) {   //Solo tengo tantas columnas como el nivel en el que estoy
                if (j < i) {    // Enlazo el actual con el de su derecha
                    adyacencias[nodo].insert(nodo+1);
                    adyacencias[nodo+1].insert(nodo);
                }
                
                if (i < n) {
                    // Enlazo el actual con el de abajo a la izquierda  
                    adyacencias[nodo].insert(nodo+i);
                    adyacencias[nodo+i].insert(nodo);
                    // Enlazo el actual con el de abajo a la derecha
                    adyacencias[nodo].insert(nodo+i+1);
                    adyacencias[nodo+i+1].insert(nodo);
                }

                ++nodo;
            }
        }
    }

};