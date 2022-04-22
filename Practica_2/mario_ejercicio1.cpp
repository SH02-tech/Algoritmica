/**
 * File: mario_ejercicio1.cpp
 *
 * ALGORITMICA, PRACTICA 2.
 * Ejercicio 1. Resolución.
 *
 * */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// generador de ejemplos para el problema del elemento en su posición. Para rellenar el vector de tamaño n, genera
// todos los enteros entre -(n-1) y (n-1) en un vector auxiliar; después obtiene una permutación aleatoria de ese
// vector, se queda con los n primeros elementos, y los ordena de forma creciente

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
 * @brief Calcula un vector de enteros aleatorios distintos ordenados de forma creciente.
 * @param n numero de elementos del vector
 * @return el vector de enteros calculado.
 * */
vector<int> vectorGenerator(int n)
{
    int m=2*n-1;

    int * T = new int[n];
    assert(T);
    int * aux = new int[m];
    assert(aux);

    srand(time(0));
    //genero todos los enteros entre -(n-1) y n-1
    for (int j=0; j<m; j++) aux[j]=j-(n-1);

    //algoritmo de random shuffling the Knuth (permutación aleatoria)
    for (int j=m-1; j>0; j--) {
        double u=uniforme();
        int k=(int)(j*u);
        int tmp=aux[j];
        aux[j]=aux[k];
        aux[k]=tmp;
    }
    //me quedo con los n primeros del vector
    for (int j=0; j<n; j++) T[j]=aux[j];
    //for (int j=0; j<n; j++) cout << T[j] << " ";

    //Y ahora ordeno el vector T
    vector<int> myvector (T, T+n);
    vector<int>::iterator it;

    sort(myvector.begin(),myvector.end());

    //for (it=myvector.begin(); it!=myvector.end(); ++it)
    //cout << " " << *it;

    delete [] aux;
    return myvector;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Búsqueda lineal del indice i que cumple v[i]==i
 * @param v vector a partir del cual realizar la busqueda
 * @param ini posicion de inicio a partir de la cual realizar la busqueda
 * @param fin posicion final a partir de la cual dejar de buscar (incluida en v)
 * @pre 0 <= ini <= fin < n
 * @return si se encuentra, devuelve el indice, sino devuelve -1
 * */
int linealSearch(vector<int> v, int ini, int fin) {
    int i = ini, tam = fin - ini + 1, index = -1;
    bool found = false;
    if(tam > 0) {
        while(i <= fin && !found) {
            if(v[i] == i) {
                index = i;
                found = true;
            }
            i++;
        }
    }
    return index;
}

/**
 * @brief Búsqueda basada en la técnica Divide y Vencerás del índice i que cumple v[i]==i
 * @param v vector ordenado ascendentemente sin repetidos a partir del cual realizar la bsqueda
 * @param ini posicion de inicio a partir de la cual realizar la busqueda
 * @param fin posicion final a partir de la cual dejar de buscar (incluida en v)
 * @pre 0 <= ini <= fin < n
 * @return si se encuentra devuelve el indice, sino devuelve -1
 */
int dcSearch(vector<int> v, int ini, int fin) {

    static const int UMBRAL = 1;   // Hay que calcular el optimo

    if( (fin - ini + 1) <= UMBRAL) {
        return linealSearch(v, ini, fin);
    } else {
        int k = (ini + fin + 1)/2;
        if(v[k] == k) {
            return k;
        } else if (v[k] > k) {
            return dcSearch(v,ini,k-1);
        } else {
            return dcSearch(v,k+1,fin);
        }
    }
}

/**
 * @brief Búsqueda basada en la técnica Divide y Vencerás del índice i que cumple v[i]==i con vector con repeticiones
 * @param v vector ordenado ascendentemente con repetidos a partir del cual realizar la bsqueda
 * @param ini posicion de inicio a partir de la cual realizar la busqueda
 * @param fin posicion final a partir de la cual dejar de buscar (incluida en v)
 * @pre 0 <= ini <= fin < n
 * @return si se encuentra devuelve el indice, sino devuelve -1
 */
//int dcSearchWithRepets(vector<int> v, int ini, int fin) {
//
//    if ( (fin - ini + 1) > 0) {
//        int k = (ini + fin + 1)/2;
//        if(v[k] == k) {
//            return k;
//        } else if (v[k] > k) {
//            return dcSearch(v,ini,k-1);
//        } else {
//            return dcSearch(v,k+1,fin);
//        }
//    }
//
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Main para probar los métodos

//int main(int argc, char * argv[]) {
//
//    if (argc !=2) {
//        cerr << "Formato: " << argv[0] << " <num_elem> " << endl;
//        return -1;
//    }
//
//    int n = atoi(argv[1]);
//
//    // Creamos el vector ordenado ascendentemente
//
//    vector<int> myvector(vectorGenerator(n));
//
//    // Procedemos a realizar la busqueda con los dos métodos
//
//    int index_ls = linealSearch(myvector,0,myvector.size()-1);
//    int index_dc = dcSearch(myvector,0,myvector.size()-1);
//
//    // Salida con los resultados
//
//    cout << "Vector (posición,valor): " << endl;
//    for (int i=0; i < myvector.size(); i++)
//        cout << " (" << i << "," << myvector[i] << ")";
//    cout << endl;
//
//    cout << "Búsqueda lineal: " << endl;
//    (index_ls == -1) ? cout << "Ningún i con v[i]==i" << endl : cout << "Indice i con v[i]==i es: " << index_ls << endl;
//    cout << "Búsqueda Divide y Vencerás: " << endl;
//    (index_dc == -1) ? cout << "Ningún i con v[i]==i" << endl : cout << "Indice i con v[i]==i es: " << index_dc << endl;
//
//    return 0;
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Main para obtener datos de la eficiencia

int main(int argc, char * argv[]) {

    if (argc !=2) {
        cerr << "Formato: " << argv[0] << " <num_elem> " << endl;
        return -1;
    }

    int n = atoi(argv[1]);

    // Creamos el vector ordenado ascendentemente

    vector<int> myvector(vectorGenerator(n));

    // Obtenemos el tiempo de ejecucion para la busqueda lineal

    clock_t tantes_bl, tdespues_bl, tantes_dc, tdespues_dc;

    tantes_bl = clock();
    linealSearch(myvector,0,myvector.size()-1);
    tdespues_bl = clock();

    tantes_dc = clock();
    dcSearch(myvector,0,myvector.size()-1);
    tdespues_dc = clock();

    // Salida de datos

    cout << n << ";"
         << (double)(tdespues_bl-tantes_bl)/(CLOCKS_PER_SEC*10E-3) << ";"
         << (double)(tdespues_dc-tantes_dc)/(CLOCKS_PER_SEC*10E-3) << endl;

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////