#include <list>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

class Graph {

    private:
    vector<bool> exist;
    vector<list<int>> connections;
    int n;
    double probability;

    public:

    Graph(int n, double p) {
        exist.resize(n, true);
        connections.resize(n);
        this->n = n;
        probability = p*100;
    }


    void printGraph() const {
        cout << "Graph with " << n << " vertices and probability " << probability << ":\n";
        for (int i = 0; i < n; ++i) {
            if (exist[i]) {
                cout << "Vertex " << i << ": ";
                for (int neighbor : connections[i]) {
                    cout << neighbor << " ";
                }
                cout << endl;
            }
        }
    }

    void addEdge(int u, int v) {
        if(find(connections[v].begin(), connections[v].end(), u) == connections[v].end()) {
            connections[u].push_back(v);
        }
    }

    bool removeEdge(int vertex, int edge) {
        if(find(connections[vertex].begin(), connections[vertex].end(), edge) != connections[vertex].end()) {
            connections[vertex].remove(edge);
            return true;
        }
        return false;

    }

    bool removeVertex(int vertex) {
        if(exist[vertex]) {
            exist[vertex] = false;
            return true;
        }
        return false;
    }

    void transformToUndirected() {
        for(int i = 0; i < n; i++) {
            for(auto it = connections[i].begin(); it != connections[i].end(); it++) {
                if(find(connections[*it].begin(), connections[*it].end(), i) == connections[*it].end()) {
                    connections[*it].push_back(i);
                }
            }
        }
    }




    int getSize() {
        return n;
    }

    int getProbability() {
        return probability;
    }

    list<int> getConnections(int vertex) {
        
        list<int> filteredConnections;
        for (int conn : connections[vertex]) {
            if (exist[conn]) {
                filteredConnections.push_back(conn);
            }
        }
        return filteredConnections;
    }
};



void nodePercolation(Graph& g) {
    int size = g.getSize();
    int probability = g.getProbability();
    for(int i = 0; i < size; i++) {
        if (rand() % 100 > probability) g.removeVertex(i);
    }
}

void edgePercolation(Graph& g) {
    int size = g.getSize();
    int probability = g.getProbability();
    for(int i = 0; i < size; i++) {
        g.getConnections(i);
        for(auto it = g.getConnections(i).begin(); it != g.getConnections(i).end(); it++) {
             if (rand() % 100 > probability) g.removeEdge(i, *it);
        }

    }
}

Graph leer_grafo() {
    int n;
    double p;
    cout << "Introduce el numero de nodos de tu grafo:" << endl;
    cin >> n;
    cout << "Introduce la probabilidad de tu grafo:" << endl;
    cin >> p;
    Graph g(n,p);
    for(int i = 0; i < n; i++) {
        int m;
        cout << "Introduce el numero de aristas del nodo " << i <<  ":" << endl;
        cin >> m;
        for(int j = 0; j < m; j++) {
            int v;
            cout << i << " -> ";
            cin >> v;
            cout << endl;
            g.addEdge(i, v);
        }
    }
    return g;
}

int main() {
    char x;
    Graph g = leer_grafo();
    int n = 0;
    int pi = -1;
    int pf = -1;
    int ps = -1;
    
    nodePercolation(g);
    g.transformToUndirected();
    g.printGraph();
}


