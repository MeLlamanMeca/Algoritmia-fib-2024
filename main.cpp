#include <iostream>
#include <ciso646>
#include <limits>
#include <string>
#include "class/graph/GraphNxN.cpp"
using namespace std;

int nini = 20;
int nfin = 10000;
int nstep = 10;
double qini = 0.0;
double qfin = 1.0;
double qstep = 0.05;
int muestras = 100;

/*  
    Este main se encarga de procesar y generar todos los grafos 
    almacenando sus datos para su posterior analisis 
*/

void seed_generator() { //Seleccionar semilla para variar la generación de grafos aleatorios y a la vez permitir recuperar resultados.
    unsigned int seed;
    while (true) {
        cout << "Introduzca una semilla: ";
        cin >> seed;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            cout << "Error: por favor, introduzca una semilla correcta. FORMATO: UNSIGNED INT" << endl;
        } else {
            break;
        }

    }
    srand(seed);
    cout << endl;
}

void debbugging() { //Función editable para debugging, no visible para el usuario final.
    //Debugging
    GraphNxN g(3);
    g.printGraph();
    GraphNxN copia = g;
    copia.edgePercolation(0.5);
    copia.printGraph();
    GraphNxN copia2 = g;
    copia2.edgePercolation(0.5);
    copia2.printGraph();
}

void usage() {
    cerr << "Error: Incorrect form of usage." << endl;
    cout << "Usage: ./program_name [type] (percolation) ([N inicial] [n final] [Salto de N] [P inicial] [P final] [Salto de P] [Muestras])" << endl;
    cout << "[type]: -info | -nxn | ... | ..." << endl;
    cout << "(percolation): -node | -edge (DEFAULT) | ... | ..." << endl;
    cout << "[compulsory] (optional)" << endl;
}

int main(int argc, char* argv[]) {
    
    if(argc <= 1) {
        usage();
    }
    else {

        if (string(argv[1]) == "-quickdev") { // Modo debug
            cout << "Modo debug activado." << endl;
            debbugging();
        }
        else if (string(argv[1]) == "-info") {
            cout << "Se generaran grafos de " << nini << " a " << nfin << " con un salto de " << nstep << " nodos." << endl;
            cout << "Se generaran grafos con una probabilidad de percolacion de " << qini << " a " << qfin << " con un salto de " << qstep << "." << endl;
            cout << "Se realizaran " << muestras << " muestras por cada grafo." << endl;
            cout << "El modo de generacion de grafos esta definido por [type] y el modo de percolacion por (percolation)." << endl;
        }
        else if(string(argv[1]) == "-nxn" || string(argv[1]) == "...") { // Modo de generación de grafos
            
            seed_generator();
            if(argc == 9) {
                nini = stoi(argv[3]);
                nfin = stoi(argv[4]);
                nstep = stoi(argv[5]);
                qini = stod(argv[6]);
                qfin = stod(argv[7]);
                qstep = stod(argv[8]);
                muestras = stoi(argv[9]);
            }

            for (int n = nini; n <= nfin; n += nstep) {
            
                Graph g;
                if(string(argv[1]) == "-nxn") g = GraphNxN(n);   // Generador de grano nxn base
                if(string(argv[1]) == "...") //g = Graph...(n);
                if(string(argv[1]) == "...") //g = Graph...(n);

                for (double q = qini; q <= qfin; q += qstep) {
                    for (int muestra = 1; muestra <= muestras; ++muestra) {
                        Graph copia = g;
                        if(argv[2] == "-node") copia.nodePercolation(q);
                        else copia.edgePercolation(q);
                        //AÑADIR PRINT DE LOS RESULTADOS g.PrintResults);
                    }
                }
            }
        }
        else {
            usage();
        }

    }
    
   
}
