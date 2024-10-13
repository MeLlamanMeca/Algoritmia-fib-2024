#include <iostream>
#include <vector>
#include <set>
#include <ciso646>
#include "Graph.cpp"
using namespace std;

class GraphKomp : public Graph {

public:
    GraphKomp() : Graph() { //Constructor por defecto
        GraphKomp(0);
    }
    
    GraphKomp(int n) : Graph() { //Constructor
        this->n = n;
        exist.resize(n, true);
        adyacencias = vector<set<int>>(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j) adyacencias[i].insert(j);
            }
        }
    }

};