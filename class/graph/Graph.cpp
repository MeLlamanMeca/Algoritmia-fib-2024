#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <ciso646>
using namespace std;

class Graph {

protected:
    int n;
    vector<bool> exist;
    vector<set<int>> adyacencias; 

public:

    Graph() {
        n = 0;
    }

    void nodePercolation(double p) { //percolacion de nodos
        int probability = p*100;
        for(int i = 0; i < n; i++) {
            if (rand() % 100 >= probability) exist[i] = false;
        }
    }

    void edgePercolation(double p) { //percolacion de aristas
        int probability = p*100;
        for(int i = 0; i < n; i++) {
            for(auto it = adyacencias[i].begin(); it != adyacencias[i].end();) {
                if(*it > i) {
                    if (rand() % 100 >= probability) {
                        int neighbor = *it;
                        it = adyacencias[i].erase(it);
                        adyacencias[neighbor].erase(i);
                    } 
                    else ++it;
                }
                else ++it;
            }
        }
    }

    double calcularCC () {
        vector<bool> visited (adyacencias.size(),false);
        queue<int> c;
            
        int cc = 0;

        for (int i = 0; i < adyacencias.size(); ++i) {

            if (not visited[i] and exist[i]) {
                ++cc;

                c.push(i);
                visited[i] = true;

                while (not c.empty()) {
                    int vertex = c.front();
                    c.pop();

                    for (int vecino : adyacencias[vertex]) {
                        if (not visited[vecino] and  exist[vecino]) {
                            c.push(vecino);
                            visited[vecino] = true;
                        }
                    }
                }
            }
        }

        double a = 0.0;
        for(bool exists : exist) {
            if(exists) ++a;
        }
        double b = cc;
        return b/a;
    }
    //Printea el grafo nxn para comprobar que se haya generado correctamente
    virtual void printGraph() const {
        cout << "Graph with " << n << " vertices:\n";
        for (int i = 0; i < n; ++i) {
            if (exist[i]) {
                cout << "Vertex " << i << ":";
                for (int neighbor : adyacencias[i]) {
                    cout << " " << neighbor;
                }
                cout << endl;
            }
        }
        cout << "----------------------------------------------" << endl;
    }

};