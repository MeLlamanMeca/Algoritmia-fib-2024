#include <iostream>
#include <vector>
#include <list>
using namespace std;

class grafoNxN {
private:
    int n;
    vector<list<int>> adyacencias; 

public:

    grafoNxN(int n) {
        this->n = n;
        //Genero el grafo
        adyacencias = vector<list<int>>(n*n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {   

                if (j+1 != n) { //Enlazado horizontal
                    adyacencias[3*i+j].push_back(3*i+j+1); 
                    adyacencias[3*i+j+1].push_back(3*i+j);
                }

                if (i != 0) {   //Enlazado vertical
                    adyacencias[3*i+j].push_back()
                }
            } 
        }
    }


    //Printea el grafo nxn para comprobar que se haya generado correctamente
    void printGrafo() {

    }

};