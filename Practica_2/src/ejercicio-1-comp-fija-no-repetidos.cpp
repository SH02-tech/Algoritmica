/**
 * @file ejercicio-1-comp-fija-no-repetidos.cpp
 * @author Mario Megías Mateo
 * @author Shao Jie Hu Chen
 * @author Jesús Samuel García Carballo
 *
 * ALGORITMICA, PRACTICA 2.
 * Ejercicio 1 sin repetición. Resolución.
 *
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <chrono>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// generador de ejemplos para el problema del elemento en su posición. Para rellenar el vector de tamaño n, genera
// todos los enteros entre -(n-1) y (n-1) en un vector auxiliar; después obtiene una permutación aleatoria de ese
// vector, se queda con los n primeros elementos, y los ordena de forma creciente

/**
 * @brief Genera un número uniformemente distribuido en el intervalo [0,1) a partir de uno de los generadores
 * disponibles en C.
 * @return número uniformemente distribuido en el intervalo [0,1)
 */
static double uniforme() {
    static int t = rand();
    static double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

/**
 * @brief Calcula un vector de enteros aleatorios distintos ordenados de forma creciente.
 * @param n numero de elementos del vector
 * @return el vector de enteros calculado. 
 */
static vector<int> vectorGenerator(int n)
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
 */
static int busquedaBasica(const vector<int> &v, int ini, int fin) {
    int i = ini, tam = fin - ini + 1, indice = -1;
    bool encontrado = false;
    if(tam > 0) {
        while(i <= fin && !encontrado) {
            if(v[i] == i) {
                indice = i;
                encontrado = true;
            }
            ++i;
        }
    }
    return indice;
}

#ifndef UMBRAL
#define UMBRAL 5 // Hay que calcular el optimo
#endif
/**
 * @brief Búsqueda basada en la técnica Divide y Vencerás del índice i que cumple v[i]==i
 * @param v vector ordenado ascendentemente sin repetidos a partir del cual realizar la bsqueda
 * @param ini posicion de inicio a partir de la cual realizar la busqueda
 * @param fin posicion final a partir de la cual dejar de buscar (incluida en v)
 * @pre 0 <= ini <= fin < n
 * @return si se encuentra devuelve el indice, sino devuelve -1
 */
static int busquedaDV(const vector<int> &v, int ini, int fin) {
    if( (fin - ini + 1) <= UMBRAL) {
        return busquedaBasica(v, ini, fin);
    } else {
        int k = (ini + fin + 1)/2;
        if(v[k] == k) {
            return k;
        } else if (v[k] > k) {
            return busquedaDV(v,ini,k-1);
        } else {
            return busquedaDV(v,k+1,fin);
        }
    }
}

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

#ifndef REPETITIONS
#define REPETITIONS 50
#endif
#ifndef SIZE_VECTOR
#define SIZE_VECTOR 20000
#endif

int main(int argc, char * argv[]) {
    

    if (argc !=2) {
        cerr << "Formato: " << argv[0] << " <num_elem> " << endl;
        return -1;
    }

    int n = atoi(argv[1]);

    static int acumulador = 0;
    static chrono::_V2::steady_clock::time_point tantes;    // Valor del reloj antes de la ejecución
    static chrono::_V2::steady_clock::time_point tdespues;  // Valor del reloj antes de la ejecución
    static vector<vector<int>> vectors(SIZE_VECTOR);
	
    for (int i=0; i<REPETITIONS; ++i) {
        for (int j=0; j<SIZE_VECTOR; ++j)
            vectors[j] = vectorGenerator(n);

        tantes = chrono::steady_clock::now();    // Valor del reloj antes de la ejecución
        for (int j=0; j<SIZE_VECTOR; ++j)
            busquedaDV(vectors[j], 0, n-1);
        tdespues = chrono::steady_clock::now();    // Valor del reloj antes de la ejecución

        acumulador += chrono::duration_cast<chrono::nanoseconds>(tdespues - tantes).count();
    }

	cout << acumulador*1.0/(REPETITIONS*SIZE_VECTOR) << endl; // Tiempo en nanosegundos. 

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////