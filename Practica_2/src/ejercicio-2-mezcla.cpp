/**
 * @file ejercicio-2-mezcla.cpp
 * @author Shao Jie Hu Chen
 * @author Jesús Samuel García Carballo
 * @author Mario Megías Mateo
 * @brief Este programa determina el tiempo que tarda en ejecutarse el algoritmo para mezclar
 * k vectores de n componentes. 
 * @param n Número de elementos de los vectores en caso normal. Número de vectores cuando KELEMENTS está definido en compilación. 
 * @return Tiempo de ejecución del algoritmo (en ms). 
 */

#include <iostream>
#include <cassert>
#include <ctime>
#include <chrono>

#include <vector>
#include <algorithm>

using namespace std;

#ifndef DEFAULT_N
#define DEFAULT_N 10
#endif

#ifndef DEFAULT_K
#define DEFAULT_K 5
#endif

/**
 * @brief Genera un número uniformemente distribuido en el intervalo [0,1) a partir de uno de los generadores
 * disponibles en C.
 * @return número uniformemente distribuido en el intervalo [0,1)
 * 
 */
double uniforme() {
	int t = rand();
	double f = ((double)RAND_MAX+1.0);
	return (double)t/f;
}

/**
 * @brief Calcula un vector de enteros aleatorios distintos ordenados de forma creciente.
 * @param n numero de elementos del vector
 * @return el vector de enteros calculado.
 */
vector<vector<int>> Generator(int n, int k) {
	vector<vector<int>> array_vectors;
	array_vectors.resize(k);

	// for (int i=0; i<k; ++i)
	// 	array_vectors[i].clear();

	int N=k*n;
	int *aux = new int[N];
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
				array_vectors[i].push_back(aux[t]);
				t++;
				m++;
			}
		}
	}

	delete [] aux;
	return array_vectors;
}

/**
 * @brief Algoritmo trivial para la unión de dos vectores, de forma que el resultado está ordenado. 
 * 
 * @param vector1 Primer vector ordenado.
 * @param vector2 Segundo vector ordenado.
 * @pre Los vectores han de estar ordenados. 
 * @return vector<int> Resultado ordenado de la unión de los vectores. 
 */
vector<int> Unifica(const vector<int> &vector1, const vector<int> &vector2) {
	vector<int> acumulador;
	auto it_vector1 = vector1.begin(); 
	auto it_vector2 = vector2.begin();

	while (it_vector1 != vector1.end() && it_vector2 != vector2.end()) {
		if (*it_vector1 < *it_vector2) {
			acumulador.push_back(*it_vector1); 
			++it_vector1; 
		}
		else {
			acumulador.push_back(*it_vector2); 
			++it_vector2;
		}
	}

	acumulador.insert(acumulador.end(), it_vector1, vector1.end());
	acumulador.insert(acumulador.end(), it_vector2, vector2.end());
	
	return acumulador;
}

/**
 * @brief Algoritmo tipo Divide y Vencerás para la unión de dos vectores, de forma que el resultado está ordenado. 
 * 
 * @param lista_vectores Lista de vectores ordenados. 
 * @pre Cada vector de la lista ha de estar ordenado. 
 * @return vector<int> Resultado ordenado de la unión de los vectores. 
 */
vector<int> Agrupa(const vector<vector<int>> &lista_vectores) {
	vector<int> acumulador;
	auto it = lista_vectores.begin();
	acumulador = *it;
	++it;

	while (it != lista_vectores.end()) {
		acumulador = Unifica(acumulador, *it);
		++it;
	}

	return acumulador;
}

int main(int argc, char **argv) {
	int n,k;

	clock_t tantes;    // Valor del reloj antes de la ejecución
	clock_t tdespues;  // Valor del reloj después de la ejecución

	if (argc != 2) {
		cerr << "Número inválido de argumentos.\n";
		exit(1);
	}

#ifdef KELEMENTS
	n = DEFAULT_N;
	k = atoi(argv[1]);
#else
	n = atoi(argv[1]);
	k = DEFAULT_K;
#endif

	vector<vector<int>> lista_vectores = Generator(n,k);

#ifdef VERBOSE
	for (int i=0; i<lista_vectores.size(); ++i) {
		for (int j=0; j<lista_vectores[i].size(); ++j)
			cout << lista_vectores[i][j] << " ";
		cout << endl;
	}
#endif

	tantes = clock();

#ifndef VERBOSE
	Agrupa(lista_vectores);
#else
	vector<int> resultado = Agrupa(lista_vectores);
#endif

	tdespues = clock();

#ifdef VERBOSE
	for (auto it = resultado.begin(); it != resultado.end(); ++it)
		cout << *it << " ";
	cout << endl;
#endif

	cout << ((double)(tdespues-tantes))/(CLOCKS_PER_SEC*1E-3)<< endl; // Tiempo en milisegundos. 

	return 0;
}
