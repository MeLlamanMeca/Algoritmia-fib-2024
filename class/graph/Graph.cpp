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
    vector<set<int>> adjacencies; 
    bool isUndirected; 
    // Graph does not contain duplicates in its list of adjacencies until isUndirected becomes true
    // addEdge, removeEdge and

    bool random(double p) {
        double random = static_cast<double>(rand()) / RAND_MAX;
        return random < p;
    }

    void transformToUndirected() {
        for(int i = 0; i < n; i++) {
            for(auto it = adjacencies[i].begin(); it != adjacencies[i].end(); it++) {
                if(adjacencies[*it].find(i) == adjacencies[*it].end()) {
                    adjacencies[*it].insert(i);
                }
            }
        }
        isUndirected = true;
    }

public:

    Graph() {
        n = 0;
        isUndirected = false;
    }

    int getSize() {
        return n;
    }

    void addEdge(int u, int v) {
        if(adjacencies[u].find(v) == adjacencies[u].end() && adjacencies[v].find(u) == adjacencies[v].end()) {
            adjacencies[u].insert(v);
        }
    }

    set<int>::iterator removeEdge(int u, int v) {
        auto it_u = adjacencies[u].find(v);
        if(it_u != adjacencies[u].end()) {
            return adjacencies[u].erase(it_u);
        }

        auto it_v = adjacencies[v].find(u);
        if(it_v != adjacencies[v].end()) {
            return adjacencies[v].erase(it_v);
        }

        return adjacencies[u].end();
    }

    bool removeVertex(int vertex) {
        if(exist[vertex]) {
            exist[vertex] = false;
            return true;
        }
        return false;
    }

    // Percolacion de nodos
    void nodePercolation(double q) {
        double p = 1.0 - q;
        for(int i = 0; i < n; i++) {
            if (random(p)) removeVertex(i);
        }
    }

    // Percolacion de aristas, verificar que esta función está bien despues de algunos cambios ---------------------------------------------------------------------
    void edgePercolation(double q) {
        double p = 1.0 - q;
        for(int i = 0; i < n; i++) {
            for(auto it = adjacencies[i].begin(); it != adjacencies[i].end();) {
                if (random(p)) it = removeEdge(i, *it);
                else ++it;
            }
        }
    }

    int calcularCC () {
        if (!isUndirected) this->transformToUndirected();
        vector<bool> visited (adjacencies.size(),false);
        queue<int> c;
            
        int cc = 0;
        for (int i = 0; i < adjacencies.size(); ++i) {
            if (not visited[i] and exist[i]) {
                ++cc;
                c.push(i);
                while (not c.empty()) {
                    int vertex = c.front();
                    c.pop();
                    visited[vertex] = true;
                    set<int>::iterator it = adjacencies[vertex].begin();
                    while (it != adjacencies[vertex].end()) {
                        if (not visited[*it] and  exist[*it]) c.push(*it);
                        ++it;
                    }
                }
            }
        }
        return cc;
    }

    // Printea el grafo nxn para comprobar que se haya generado correctamente
    void printGraph() const {
        cout << "Graph with " << n << " vertices:\n";
        for (int i = 0; i < n; ++i) {
            if (exist[i]) {
                cout << "Vertex " << i << ":";
                for (int neighbor : adjacencies[i]) {
                    cout << " " << neighbor;
                }
                cout << endl;
            }
        }
        cout << "----------------------------------------------" << endl;
    }


};