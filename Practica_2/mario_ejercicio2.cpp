/**
 * File: mario_ejercicio1.cpp
 *
 * ALGORITMICA, PRACTICA 2.
 * Ejercicio 2. Resolución.
 *
 * */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <climits>
#include <cassert>
//#include <algorithm>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// generador de ejemplos para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma
// creciente cada uno con n elementos, genera un vector de tamaño k*n con todos los enteros entre 0 y kn-1 ordenados.
// Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tamaño n para obtener los k vectores.
// Están ordeados porque el algoritmo de muestreo mantiene el orden

/*
 * @brief Genera un número uniformemente distribuido en el intervalo [0,1) a partir de uno de los generadores
 * disponibles en C.
 * @return número uniformemente distribuido en el intervalo [0,1)
 * */
double uniforme() {
    int t = rand();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

/*
 * @brief Calcula un vector de vector de enteros aleatorios distintos ordenados de forma creciente.
 * @param n tamaño de los vectores
 * @param k tamaño de los vectores
 * @return el vector de vector de enteros calculado.
 * */
vector<vector<int>> vectorsGenerator(int n, int k) {

    int **T;
    T =  new int * [k];
    assert(T);

    for (int i = 0; i < k; i++)
        T[i]= new int [n];

    int N=k*n;
    int * aux = new int[N];
    assert(aux);

    srand(time(0));

    //genero todos los enteros entre 0 y k*n-1
    for (int j=0; j<N; j++) aux[j]=j;

    //para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
    for (int i=0; i<k; i++) {
        int t=0;
        int m=0;
        while (m<n) {
            double u=uniforme();
            if ((N-t)*u >= (n-m)) t++;
            else {
                T[i][m]=aux[t];
                t++;
                m++;
            }
        }
    }

    delete [] aux;

    vector<vector<int>> v;
    for (int i=0; i<k; i++) {
        v.push_back(vector<int>(T[i],T[i]+n));
    }

    return v;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * @brief Construye un vector ordenado ascendente de tamaño k*n a partir de k vectores ordenados ascendentemente
 * de tamaño n.
 * @param v contenedor con los k vectores de tamaño n
 * @pre v[i].size() == v[j].size() para 0 <= i,j < n, y que no este vacio
 * @return el vector ordenado de tamaño k*n
 **/
vector<int> basicSortingVectors(vector<vector<int>> v) {

    // Creamos el vector solución con k*n componentes inizializado a -1
    int k = v.size(), n = v[0].size(), tam = k * n;
    vector<int> solution(tam,-1);

    // Inicializamos las primeras n componentes con los valores de v[0]
    //////////// ¿¿¿¿¿LIMIT???????? Para ver si se pueden mejorar las constantes ocultas
    for (int i = 0; i < n; i++) {
        solution[i] = v[0][i];
    }

    int i = 1;                                                  // Fija el vector fila número i de v
    while (i < k) {                                             // Mientras no hayamos recorrido v
        vector<int> aux(solution);
        int indexAux = 0, indexV = 0, newSizeSolution = (i+1)*n, auxSize = i*n;
        for (int j=0; j < newSizeSolution; j++) {
            if ( (v[i][indexV] < aux[indexAux] && indexV < n) || indexAux == auxSize) {
                solution[j] = v[i][indexV];
                indexV++;
            } else if (indexAux < auxSize) {
                solution[j] = aux[indexAux];
                indexAux++;
            }
        }
        i++;
    }

    return solution;
}

/**
 * @brief Construye un vector ordenado asc. de tamaño 2n a partir de dos vectores ordenados asc. de tamaño n
 */
//void sorting2vectors(vector<vector<int>> v, vector<int> s) {
//}

/**
 * @brief Construye un vector ordenado asc. de tamaño kn a partir de k vectores ordenados asc. de tamaño n, usando
 * la técnica de divide y vencerás.
 * @param v conjunto de k vectores de tamaño n ordenados asc.
 * @pre v.size() > 2
 * @return el vector de tamaño kn ordenado asc.
 */
//void dcSortingVectors(vector<vector<int>> v, vector<int> s) { // s tiene que tener tamaño v[0].size()*2
//
//    int k = v.size(), n = v[0].size();
//    if (k == 2) {
//        sorting2vectors(v,s);
//    } else {
//        int newSizeV = k/2;
//        vector<vector<int>> v1, v2;
//        for (int i = 0; i < newSizeV; ++i) {
//            if (i < k/2) {
//                v1.push_back(v[i]);
//            } else {
//                v2.push_back(v[i]);
//            }
//        }
//        vector<int> s1,s2;
//        dcSortingVectors(v1,s1);
//        dcSortingVectors(v2,s2);
//
//    }
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char * argv[]) {

    if (argc != 3) {
        cerr << "Formato: " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    // Creamos el vector de vectores ordenados ascendentemente

    vector<vector<int>> myvectors(vectorsGenerator(n,k));

    // Procedemos a realizar el calculo del vector resultado

    vector<int> solution(basicSortingVectors(myvectors));

    // Salida con los resultados

    cout << "Conjunto de vectores original: " << endl;
    for (int i=0; i < k; i++) {
        for (int j = 0; j < n; ++j) {
            cout << setw(5) << myvectors[i][j];
        }
        cout << endl;
    }

    cout << endl;
    cout << "Vector resultado ordenado: " << endl;
    for (int i = 0; i < k*n; ++i) {
        cout << " " << solution[i];
    }
    cout << endl;

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////