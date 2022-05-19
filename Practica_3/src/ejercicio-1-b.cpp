#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////

struct myclass {
    bool operator() (int i,int j) { return (i>j);}
} myobject;

int sumaPesos(const vector<int> & pesos) {
    int suma = 0;
    for (auto it = pesos.begin(); it != pesos.end(); ++it) {
        suma += *it;
    }
    return suma;
}

bool esFactible(const int K, const vector<int> & pesos, int nuevoPeso) {
    return ( (sumaPesos(pesos) + nuevoPeso) <= K);
}

bool esSolucionOptima(const int K, const vector<int> & pesos) {
    return (sumaPesos(pesos) == K);
}

vector<int> maxWeight (const int K, vector<int> pesos) {

    sort(pesos.begin(), pesos.end(), myobject);   // ordenamos en orden decreciente
    vector<int> solucion; 
    solucion.clear();
    int pesoCandidato;

    // Mientras la lista no sea vacía y no sea la solucion optima
    while ( !esSolucionOptima(K, solucion) && !pesos.empty()) { 

        pesoCandidato = pesos.front();  // Escogemos el menor peso
        pesos.erase(pesos.begin());  // Lo eliminamos del conjunto de candidatos

        if (esFactible(K, solucion, pesoCandidato)) {
            solucion.push_back(pesoCandidato);
        }
    }

    return solucion;
}

void imprimeVector(vector<int> v) {
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        cerr << "ERROR, ARGUMENTOS: <nombre_programa> <CargaTotal> <peso_1> <peso_2> ... <peso_n>";
        exit(EXIT_FAILURE); 
    }  

    int K = atoi(argv[1]);
    int array_pesos[argc-2]; 

    for (int i=2; i < argc; i++) {
        array_pesos[i-2] = atoi(argv[i]);
    }

    // for (size_t i = 0; i < sizeof(array_pesos)/sizeof(array_pesos[0]); i++)
    // {
    //     cout << array_pesos[i] << " ";
    // }
    // cout << endl;
    
    vector<int> pesos(array_pesos, array_pesos + sizeof(array_pesos)/sizeof(array_pesos[0]));

    cout << "Carga total: " << K << endl;
    cout << "Vector de los pesos de los contenedores (Peso=" << sumaPesos(pesos) << "):" << endl;
    imprimeVector(pesos);

    vector<int> solucion(maxWeight(K, pesos));

    cout << "Vector de los pesos de la solucion (Peso=" << sumaPesos(solucion) << "):" << endl;
    imprimeVector(solucion);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////