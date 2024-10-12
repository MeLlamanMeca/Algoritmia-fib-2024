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

/* como debería calcular r debería pasarla como parámetro
 con la creadora? O sino por una n determinada generar aleatoriamente
 una r entre ciertos valores determinados [x,y]?
 
    se dice que r ~ sqrt(ln(n)/n))
*/

private:
    double r; 
    vector<pair<double,double>> plano;//indica coordenadas de cada nodo i
public:
    RandGeomGraph() : Graph(){ //Constructor por defecto
        RandGeomGraph(0);
    }
    
    RandGeomGraph(int n, double r_param = -1) : Graph() { 
        this->n = n;
        //PRIMERA DUDA, como hacer la R
        if (r_param < 0) this->r = sqrt(log(n) / n); //Si no entra ninguna r la calculamos
        else this->r = r_param; // Usar el r proporcionado
        //¿MEJOR generar n random cercana a este valor tipo, pe r = ans +=[-0.1,+0.1]?
        exist.resize(n*n, true);//inútil, no eliminaremos nunca vértices
        plano.resize(n);
        adyacencias = vector<set<int>>(n*n);
        //generar cordenada aleatoria plano[i] para cada nodo i
        srand(static_cast<unsigned int>(time(0))); // Semilla para números aleatorios
        for (int i = 0; i < n; ++i) {
            double x = static_cast<double>(rand()) / RAND_MAX * (n-1); // Coordenada x entre 0 y n
            double y = static_cast<double>(rand()) / RAND_MAX * (n-1); // Coordenada y entre 0 y n
            plano[i] = make_pair(x, y);
        }
        // Conectar los nodos si la distancia euclidiana entre ellos es <= r
        for (int i = 0; i < n; ++i) {//O(n^2)
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

    // distancia(x1, y1) y (x2, y2) = sqrt((x1-x2)^2+(y1-y2)^2)
    double distancia(const pair<double, double>& p1, const pair<double, double>& p2) const {
        return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
    }
};