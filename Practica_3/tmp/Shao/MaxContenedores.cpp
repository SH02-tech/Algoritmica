/* MaxContendores.cpp
 *
 * Devuelve máximo número de contenedores entre c1,c2,...,cn posibles contenedores de 
 * peso p1,p2,...,pn, sujeto a una capacidad máxima k.
 *
 * Formato de entrada:
 * 1º Capacidad del buque (k)
 * 2º Número de contenedores
 * 3º Línea con pesos asociados a cada contenedor (línea con k componentes).
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	
	// Variables
	int k, num_contenedores;   	// Entrada
	vector<int> pesos;			// Entrada
	vector<int> solucion;		// Salida

	// Entrada de datos
	
	cin >> k;
	cin >> num_contenedores;

	int subpeso = 0;

	for (int i=0; i<num_contenedores; ++i) {
		cin >> subpeso;
		pesos.push_back(subpeso);
	}
	
	// Algoritmo Greedy
		
	sort(pesos.begin(), pesos.end());
	
	int peso_acumulado = 0;
	int pos = 0;

	for (int i=0; i<num_contenedores && (peso_acumulado + pesos[i]) <= k; ++i) {
		solucion.push_back(pesos[i]);
		peso_acumulado += pesos[i];
	}

	// Salida de datos
	
	cout << "Num de contenedores: " << solucion.size() << ".\n";

	return 0;
}
