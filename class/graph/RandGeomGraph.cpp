#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include "Graph.cpp"
using namespace std;

class RandGeomGraph : public Graph {//solo haremos edgePercolation()

//Sea G = (V,E)
//∀ u,v ∈ V, u~v <-> distanciaEuclidiana(u,v) <= radio
protected:
    double r; 
    vector<pair<double,double>> plano;//indica coordenadas ∈ [0,1) de cada nodo i  
    
    // distancia(x1, y1) y (x2, y2) = sqrt((x1-x2)^2+(y1-y2)^2)
    double distancia(const pair<double, double>& p1, const pair<double, double>& p2) const {
        return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
    }

public:
    RandGeomGraph(){ //Constructor por defecto
        RandGeomGraph(0);
    }
    
    RandGeomGraph(int n) { 
        this->n = n;
        this->r = sqrt(log(n)/n);
        exist.resize(n, true);
        plano.resize(n);
        adyacencias = vector<set<int>>(n);
        //generar cordenada aleatoria plano[i] para cada nodo i
        srand(static_cast<unsigned int>(time(0))); // Semilla para números aleatorios
        for (int i = 0; i < n; ++i) {
            double x = static_cast<double>(rand()) / RAND_MAX; // Coordenada x entre 0 y 1
            double y = static_cast<double>(rand()) / RAND_MAX; // Coordenada y entre 0 y 1
            plano[i] = make_pair(x, y);
        }
        // Conectar los nodos si la distancia euclidiana entre ellos es <= r
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    if (distancia(plano[i], plano[j]) <= r) {
                        adyacencias[i].insert(j);
                        adyacencias[j].insert(i);
                    }
                }
            }
        }
    }

    // Función TEMPORAL para imprimir el grafo con el radio y los puntos de cada vértice, 
    void printGraph() const { // Forma alternativa a printGraph, aunque printGraph funciona igualmente
        cout << "Grafo con " << n << " vertices y radio = " << r << ":\n";
        for (int i = 0; i < n; ++i) {
            if (exist[i]) {
                cout << "Vertex " << i << " (" << plano[i].first << ", " << plano[i].second << "):";
                for (int neighbor : adyacencias[i]) {
                    cout << " " << neighbor;
                }
                cout << endl;
            }
        }
        cout << "----------------------------------------------" << endl;
    }
};

class RandGeomGraphnodePercol : public RandGeomGraph {
public:

    RandGeomGraphnodePercol() : RandGeomGraph() {}

    RandGeomGraphnodePercol(int n, double probability) : RandGeomGraph(n) {
        double p = probability*100;
        for (int i = 0; i < n; ++i) {
            if (rand() % 100 >= p) exist[i] = false;
        }
    }
};

class RandGeomGraphvertexPercol : public RandGeomGraph {
public:

    RandGeomGraphvertexPercol() : RandGeomGraph() {}

    RandGeomGraphvertexPercol(int n, double probability) { 
        double p = probability*100;
        this->n = n;
        this->r = sqrt(log(n)/n);
        exist.resize(n, true);
        plano.resize(n);
        adyacencias = vector<set<int>>(n);
        //generar cordenada aleatoria plano[i] para cada nodo i
        srand(static_cast<unsigned int>(time(0))); // Semilla para números aleatorios
        for (int i = 0; i < n; ++i) {
            double x = static_cast<double>(rand()) / RAND_MAX; // Coordenada x entre 0 y 1
            double y = static_cast<double>(rand()) / RAND_MAX; // Coordenada y entre 0 y 1
            plano[i] = make_pair(x, y);
        }
        // Conectar los nodos si la distancia euclidiana entre ellos es <= r
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    if (distancia(plano[i], plano[j]) <= r and rand() % 100 < p) {
                        adyacencias[i].insert(j);
                        adyacencias[j].insert(i);
                    }
                }
            }
        }
    }
};