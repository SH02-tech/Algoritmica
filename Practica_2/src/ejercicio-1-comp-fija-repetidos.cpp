/**
 * @file ejercicio-1-comp-fija-repetidos.cpp
 * @author Shao Jie Hu Chen
 * @author Jesús Samuel García Carballo
 * @author Mario Megías Mateo
 * @brief Este programa determina el tiempo que tarda en ejecutarse el algoritmo para encontrar
 * encontrar vectores de tipo IC. 
 * @param nelements Número de elementos de un vector aleatorio a considerar.
 * @return Tiempo de ejecución del algoritmo (en ms). 
 */

#include <iostream>
#include <cassert>
#include <ctime>
#include <chrono>

#include <vector>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#define SEPARATION 2
#define NULL_POS -1

#ifndef UMBRAL
#define UMBRAL 5
#endif

// generador de ejemplos para el problema del elemento en su posición. Para rellenar el vector de tamaño n, genera
// todos los enteros entre -(n-1) y (n-1) en un vector auxiliar; después obtiene una permutación aleatoria de ese
// vector, se queda con los n primeros elementos, y los ordena de forma creciente

/**
 * @brief Genera un número uniformemente distribuido en el intervalo [0,1) a partir de uno de los generadores
 * disponibles en C.
 * @return número uniformemente distribuido en el intervalo [0,1)
 * 
 */
double Uniforme() {
    int t = rand();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}

/**
 * @brief Calcula un vector de enteros aleatorios distintos ordenados de forma creciente.
 * @param n numero de elementos del vector
 * @return el vector de enteros calculado.
 */
vector<int> VectorGenerator(int n) {
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
        double u=Uniforme();
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

/**
 * @brief Algoritmo trivial para la búsqueda del índice (estructura semejante a la búsqueda lineal).
 * 
 * @param v Vector a considerar.
 * @param inicial Posicion inicial.
 * @param final Posición final.
 * @return int Posición cuyo valor es igual a ella. -1 si hay error. 
 */
static int PosTipoICTrivial(const vector<int> &v, int inicial, int final) {
	int pos = NULL_POS;

	for (int i=inicial; i<=final && pos == NULL_POS; ++i)
		if (v[i] == i)
			pos = i;

	return pos;
}

/**
 * @brief Algoritmo de tipo divide y vencerás para la búsqueda del índice.
 * 
 * @param v Vector a considerar.
 * @param inicial Posicion inicial.
 * @param final Posición final.
 * @return int Posición cuyo valor es igual a ella. -1 si hay error. 
 */
static int PosTipoIC(const vector<int> &v, int inicial, int final) {
	int pos = NULL_POS;
	
	if ((final - inicial +1) <= UMBRAL) {
		pos = PosTipoICTrivial(v, inicial, final);
	} else {
		int media = (inicial+final)/2;
		int aux;
		
		aux = PosTipoIC(v, inicial, media);
		if (aux != NULL_POS) {
			pos = aux;
		} else {
			aux = PosTipoIC(v, media+1, final);
			if (aux != NULL_POS)
				pos = aux;
		}
	}

	return pos;
}

int main(int argc, char **argv) {
	
	if (argc != 2) {
		cerr << "Non valid argument format.\n";
		exit(1);
	}

	vector<int> vect = VectorGenerator(atoi(argv[1]));

	// for (auto it = vect.begin(); it != vect.end(); ++it)
	// 	cout << *it << " ";

	#ifdef PRECISION
	static chrono::_V2::steady_clock::time_point tantes;    // Valor del reloj antes de la ejecución
    static chrono::_V2::steady_clock::time_point tdespues;  // Valor del reloj antes de la ejecución

	tantes = chrono::steady_clock::now();    // Valor del reloj antes de la ejecución
	PosTipoIC(vect, 0, vect.size()-1);
	tdespues = chrono::steady_clock::now();    // Valor del reloj antes de la ejecución

	cout << chrono::duration_cast<chrono::nanoseconds>(tdespues - tantes).count() << endl; // Tiempo en milisegundos. 
	#else
	clock_t tantes;    // Valor del reloj antes de la ejecución
	clock_t tdespues;  // Valor del reloj después de la ejecución

	tantes = clock();
	PosTipoIC(vect, 0, vect.size()-1);
	tdespues = clock();

	cout << ((double)(tdespues-tantes))/(CLOCKS_PER_SEC*1E-3)<< endl; // Tiempo en milisegundos. 
	#endif
	return 0;
}
