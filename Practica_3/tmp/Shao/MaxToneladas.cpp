/**
 * @file MaxToneladas.cpp
 * 
 * Se tiene un buque mercante con capacidad de carga K toneladas.
 * Este programa implementa un algoritmo greedy para maximizar 
 * el número de toneladas en la carga.
 * 
 * Formato de entrada;
 * 1. Peso máximo (K)
 * 2. Num de contenedores.
 * 3. Peso de cada contenedor (recomendado ordenadas de menor a mayor).
 */

#include <iostream>
#include <vector>
#include <algorithm>	// sort (si es necesario)

using namespace std;

int main() {
	
	int k, num_contenedores; 		// Entrada
	vector<int> pesos;				// Entrada
	vector<int> solucion;			// Salida

	// Entrada de datos
	
	cin >> k >> num_contenedores;

	for (int i=0; i<num_contenedores; ++i) {
		int peso;

		cin >> peso;
		
		pesos.push_back(peso);
	}

	// Operaciones

	sort(pesos.begin(), pesos.end());	// No necesario si los datos ya están ordenados.

	int acumulado = 0;
	int pos = pesos.size()-1;
	int peso = pesos[pos];

	while ((peso+acumulado)<=k && pos >= 0) {
		solucion.push_back(peso);
		acumulado += peso;

		// Preparamos siguiente iteración
		--pos;
		peso = pesos[pos];
	}

	// Salida de datos
	
	for (int i=0; i<solucion.size(); ++i)
		cout << solucion[i] << " ";

	cout << "\nTotal: " << acumulado << "\n";

	return 0;
}
