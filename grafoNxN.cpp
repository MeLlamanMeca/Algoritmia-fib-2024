#include <iostream>
#include <vector>
#include <list>
using namespace std;

class grafoNxN {
private:
    int n;
    vector<bool> exist;
    vector<list<int>> adyacencias; 

public:

    grafoNxN(int n) {
        this->n = n;
        exist.resize(n*n, true);
        //Genero el grafo
        adyacencias = vector<list<int>>(n*n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {   

                if (j+1 != n) { //Enlazado horizontal
                    adyacencias[3*i+j].push_back(3*i+j+1); 
                    adyacencias[3*i+j+1].push_back(3*i+j);
                }

                if (i != 0) {   //Enlazado vertical
                    adyacencias[3*i+j].push_back(3*(i-1)+j);
                    adyacencias[3*(i-1)+j].push_back(3*i+j);
                }
            } 
        }
    }


    //Printea el grafo nxn para comprobar que se haya generado correctamente
    void printGraph() const {
        cout << "Graph with " << n << " vertices:\n";
        for (int i = 0; i < n; ++i) {
            cout << "Vertex " << i << ": ";
            for (int neighbor : adyacencias[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void nodePercolation(double p) { //percolacion de nodos
        int size = n*n;
        int probability = p*100;
        for(int i = 0; i < size; i++) {
            if (rand() % 100 > probability) g.removeVertex(i);
        }
    }

    void edgePercolation(double p) { //percolacion de aristas
        int size = n*n;
        int probability = p*100;
        for(int i = 0; i < size; i++) {
            for(auto it = adyacencias[i].begin(); it != adyacencias[i].end(); it++) {
                if (rand() % 100 > probability) it = adyacencias[i].erase(it);
            }
    }
}

};