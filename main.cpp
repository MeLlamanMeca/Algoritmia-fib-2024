#include <iostream>
#include <ciso646>
#include <limits>
#include <string>
#include "class/graph/GraphNxN.cpp"
#include "class/graph/GraphTrg.cpp"
#include "class/graph/RandGeomGraph.cpp"
using namespace std;

/*  
    Este main se encarga de procesar y generar todos los grafos 
    imprimiendo sus datos para su posterior analisis 
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
    RandGeomGraph g5 = RandGeomGraph(10);
    cout << "Sin percolar" << endl;
    g5.printGraph();
    g5.edgePercolation(0.5);
    cout << "Percolado con q = 0.5" << endl;
    g5.printGraph();
}

void usage() {
    cerr << "Error: Incorrect form of usage." << endl;
    cout << "Usage: ./program_name [type] [percolation] ([N inicial] [n final] [Salto de N] [P inicial] [Numero de saltos] [Salto de P] [Muestras])" << endl;
    cout << "[type]: -info | -nxn | -rgg | ..." << endl;
    cout << "[percolation]: -node | -edge (DEFAULT) | ... | ..." << endl;
    cout << "[compulsory] (optional)" << endl;
}

int main(int argc, char* argv[]) {
    
    if(argc <= 1) {
        usage();
    }
    else {

        int nini = 200;
        int nfin = 10000;
        int nstep = 200;
        double qini = 0.0;
        int qnum = 11;
        double qstep = 0.1;
        int muestras = 30;

        if (string(argv[1]) == "-quickdev") { // Modo debug
            cout << "Modo debug activado." << endl;
            seed_generator();
            debbugging();
        }
        else if (string(argv[1]) == "-info") {
            cout << "Se generaran grafos de " << nini << " a " << nfin << " con un salto de " << nstep << " nodos." << endl;
            cout << "Se generaran grafos con una probabilidad de percolacion de " << qini << ", " << qnum << " veces con un salto de " << qstep << "." << endl;
            cout << "Se realizaran " << muestras << " muestras por cada grafo." << endl;
            cout << "Puedes editar estos parametros de forma opcional" << endl;
            cout << "El modo de generacion de grafos esta definido por [type] y el modo de percolacion por (percolation)." << endl;
        }
        else if(string(argv[1]) == "-nxn" || string(argv[1]) == "-rgg" || string(argv[1]) == "-trg") { // Modo de generación de grafos
            
            seed_generator();
            if (argc == 10) {
                nini = stoi(argv[3]);
                nfin = stoi(argv[4]);
                nstep = stoi(argv[5]);
                qini = stod(argv[6]);
                qnum = stoi(argv[7]);
                qstep = stod(argv[8]);
                muestras = stoi(argv[9]);
            }
            
            int lastN = -1;

            for (int n = nini; n <= nfin; n += nstep) {
                if (string(argv[1]) == "-rgg" or lastN != int(sqrt(n))) {
                    double q = qini;
                    for (int qcont = 1; qcont <= qnum; ++qcont) {
                        double media = 0.0;
                        for (int muestra = 1; muestra <= muestras; ++muestra) {
                            Graph g;
                            if(string(argv[1]) == "-nxn") { // Generador de grafo nxn base
                                if(string(argv[2]) == "-node") g = GraphNxNnodePercol(sqrt(n), q);
                                else if(string(argv[2]) == "-edge") g = GraphNxNedgePercol(sqrt(n), q);
                                lastN = sqrt(n);
                            }
                            else if(string(argv[1]) == "-rgg") { // Generador de grafo aleatorio
                                if(string(argv[2]) == "-node") g = RandGeomGraphnodePercol(n, q);//no lo hacemos nunca
                                else if(string(argv[2]) == "-edge")  {
                                    //tiene que tener 1cc, la creadora lo asegura
                                    g = RandGeomGraph(n);  
                                    g.edgePercolation(q);
                                }
                                lastN = n;
                            }
                            else if(string(argv[1]) == "-trg") { // Generador de grafo triangular
                                if(string(argv[2]) == "-node") g = GraphTrgnodePercol(sqrt(n), q);
                                else if(string(argv[2]) == "-edge")  g = GraphTrgedgePercol(sqrt(n), q);
                                lastN = sqrt(n);
                            }  
                            media += g.calcularCC();
                        }
                        media /= muestras;

                        //Printear
                        if(string(argv[1]) == "-nxn") {
                            int num = sqrt(n);
                            cout << "N: " << num*num << " Q: " << q << " Media %CC: " << media <<endl;
                        }
                        else if (string(argv[1]) == "-trg") {
                            int num = sqrt(n);
                            num = (num*(num+1))/2;
                            cout << "N: " << num << " Q: " << q << " Media %CC: " << media <<endl;
                        }
                        else cout << "N: " << n << " Q: " << q << " Media %CC: " << media <<endl;
                        q += qstep;
                    }
                }   
            }
            
        }
        else {
            usage();
        }
    }
}
