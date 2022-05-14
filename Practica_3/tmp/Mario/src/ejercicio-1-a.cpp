#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////

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

bool esSolucion(const int K, const vector<int> & pesos, int nuevoPeso) {
    return esFactible(K, pesos, 0) && !esFactible(K, pesos, nuevoPeso);
}

vector<int> nContenedoresMax (const int K, vector<int> pesos) {

    sort(pesos.begin(), pesos.end());   // ordenamos en orden creciente
    vector<int> solucion; 
    solucion.clear();

    bool esSolu = false;
    int pesoCandidato;

    // Mientras no haya solución y la lista no sea vacía
    while (!esSolu && !pesos.empty()) { 

        pesoCandidato = pesos.front();  // Escogemos el menor peso
        pesos.erase(pesos.begin());  // Lo eliminamos del conjunto de candidatos

        if (esFactible(K, solucion, pesoCandidato)) {
            solucion.push_back(pesoCandidato);
        }

        esSolu = esSolucion(K, solucion, pesos.front()); // Comprobamos si es solucion
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
        cerr << "ERROR, ARGUMENTOS: <nombre_programa> <CargaTotal> <peso_1> <peso_2> ... <peso_n>" << endl;
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

    vector<int> solucion(nContenedoresMax(K, pesos));

    cout << "Vector de los pesos de la solucion (nºContenedores=" 
         << solucion.size() << ", Peso=" << sumaPesos(solucion) << "):" << endl;

    imprimeVector(solucion);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////