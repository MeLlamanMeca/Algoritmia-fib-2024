#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <ciso646>
#include "Graph.cpp"
using namespace std;

class GraphNxN : public Graph {

public:
    GraphNxN() : Graph() { //Constructor por defecto
        GraphNxN(0);
    }
    
    GraphNxN(int n) : Graph() { //Constructor
        this->n = n*n;
        exist.resize(n*n, true);
        adyacencias = vector<set<int>>(n*n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {   

                if (j+1 != n) { //Enlazado horizontal
                    adyacencias[n*i+j].insert(n*i+j+1); 
                    adyacencias[n*i+j+1].insert(n*i+j);
                }

                if (i != 0) {   //Enlazado vertical
                    adyacencias[n*i+j].insert(n*(i-1)+j);
                    adyacencias[n*(i-1)+j].insert(n*i+j);
                }
            } 
        }
    }

};

class GraphNxNnodePercol : public GraphNxN {
public:

    GraphNxNnodePercol() : GraphNxN() {}

    GraphNxNnodePercol(int n, double probability) : GraphNxN(n) {
        double p = probability*100;
        for (int i = 0; i < this->n; ++i) {
            if (rand() % 100 >= p) exist[i] = false;
        }
    }
};

class GraphNxNedgePercol : public GraphNxN {
public:
    GraphNxNedgePercol() : GraphNxN() {}

    GraphNxNedgePercol(int n, double probability) {
        double p = probability*100;
        this->n = n*n;
        exist.resize(n*n, true);
        adyacencias = vector<set<int>>(n*n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {   

                if (j+1 != n and rand() % 100 < p) { //Enlazado horizontal
                    adyacencias[n*i+j].insert(n*i+j+1); 
                    adyacencias[n*i+j+1].insert(n*i+j);
                }

                if (i != 0 and rand() % 100 < p) {   //Enlazado vertical
                    adyacencias[n*i+j].insert(n*(i-1)+j);
                    adyacencias[n*(i-1)+j].insert(n*i+j);
                }
            } 
        }
    }
};