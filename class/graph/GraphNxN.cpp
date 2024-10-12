#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <ciso646>
using namespace std;

class GraphNxN : public Graph {

public:
    GraphNxN() : Graph() { // Constructor por defecto
        GraphNxN(0);
    }
    
    GraphNxN(int n) : Graph() { //Constructor
        this->n = n*n;
        exist.resize(n*n, true);
        adjacencies = vector<set<int>>(n*n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {   
                // Enlazado horizontal
                if (j+1 != n) this->addEdge(3*i+j, 3*i+j+1);
                //Enlazado vertical
                if (i != 0) this->addEdge(3*i+j, 3*(i-1)+j);
            } 
        }
    }

};