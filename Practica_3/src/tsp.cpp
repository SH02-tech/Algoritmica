/**
 * @file tsp.cpp
 * @author Equipo Rojo
 * @brief Este programa aborda el problema del viajante del comercio
 * aplicando las heurísticas proporcionadas: vecino más cercano e inserción. 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip> // setw

using namespace std;

/* Generales ------------------------------------------------------------*/

struct Punto2D {
	double x;
	double y;

	Punto2D(double pos_x, double pos_y) :x(pos_x), y(pos_y) {}
};

struct Arco {
	int ind_inicial;
	int ind_final;
	int distancia;

	Arco(int el_inicio, int el_final, int la_distancia)
		:ind_inicial(el_inicio), ind_final(el_final), distancia(la_distancia) {}
};

int DistanciaEuclidea(const Punto2D &uno, const Punto2D &otro) {
	double diff_x = uno.x - otro.x;
	double diff_y = uno.y - otro.y;

	return sqrt((diff_x*diff_x + diff_y*diff_y));
}

vector<vector<int>> CalculaMatrizAdyacencia(const vector<Punto2D> &puntos) {
	vector<vector<int>> matriz_adyacencia(puntos.size());

	for (int i=0; i<puntos.size(); ++i) {
		for (int j=0; j<puntos.size(); ++j) {
			int distancia = DistanciaEuclidea(puntos[i], puntos[j]);
			matriz_adyacencia[i].push_back(distancia);
		}
	}

	return matriz_adyacencia;
}

int DistanciaTotal(const vector<Arco> &ciclo) {
	int total = 0;

	for (int i=0; i<ciclo.size(); ++i)
		total += ciclo[i].distancia;

	return total;
}

/* Heurística 1 ------------------------------------------------------------*/

int PosMinValida(const vector<int> &vect, const vector<bool> &banderas) {
	int pos_min = 0;

	while (banderas[pos_min])
		++pos_min;

	for (int pos = pos_min+1; pos < vect.size(); ++pos) {
		if (vect[pos] < vect[pos_min] && !banderas[pos]) {
			pos_min = pos;
		}
	}

	if (pos_min == vect.size())
		pos_min = -1;

	return pos_min;
}

vector<Arco> CicloVecinoMasCercano(const vector<vector<int>> &matriz_adyacencia) {
	vector<Arco> ciclo;

	vector<bool> banderas(matriz_adyacencia.size(), false);

	int ind_inicial = 0;
	banderas[ind_inicial] = true;
	int ind_final = PosMinValida(matriz_adyacencia[ind_inicial], banderas);

	while (ind_final >= 0) {
		ciclo.push_back(Arco(ind_inicial, ind_final,
								matriz_adyacencia[ind_inicial][ind_final]));
		banderas[ind_final] = true;

		// Preparamos siguiente iteración.
		ind_inicial = ind_final;
		ind_final = PosMinValida(matriz_adyacencia[ind_inicial], banderas);
	}

	// Cerramos ciclo

	if (!ciclo.empty()) {
		ind_inicial = ciclo[ciclo.size()-1].ind_final;
		ind_final = ciclo[0].ind_inicial;

		ciclo.push_back(Arco(ind_inicial, ind_final,
						matriz_adyacencia[ind_inicial][ind_final]));
	}

	return ciclo;
}

/* Heurística 2 -----------------------------------------------------------------------*/

struct InsercionCandidata {
	int ind_ciudad;
	int ind_insercion;
	int variacion;

	InsercionCandidata() :ind_ciudad(-1), ind_insercion(-1), variacion(-1) {};

	InsercionCandidata(int el_ind_ciudad) {
		ind_ciudad = el_ind_ciudad;
		ind_insercion = -1;
		variacion = -1;
	}

	InsercionCandidata(int el_ind_ciudad, int el_ind_insercion, int la_variacion) {
		ind_ciudad = el_ind_ciudad;
		ind_insercion = el_ind_insercion;
		variacion = la_variacion;
	}
};

int IndPuntoNorte(const vector<Punto2D> &nube) {
	int pos_norte = -1;

	if (!nube.empty()) {
		pos_norte = 0;

		for (int i=pos_norte+1; i<nube.size(); ++i) {
			if (nube[i].y > nube[pos_norte].y) {
				pos_norte = i;
			}
		}
	}

	return pos_norte;
}

int IndPuntoOeste(const vector<Punto2D> &nube) {
	int pos_oeste = -1;

	if (!nube.empty()) {
		pos_oeste = 0;

		for (int i=pos_oeste+1; i<nube.size(); ++i) {
			if (nube[i].x < nube[pos_oeste].x) {
				pos_oeste = i;
			}
		}
	}

	return pos_oeste;
}

int IndPuntoEste(const vector<Punto2D> &nube) {
	int pos_este = -1;

	if (!nube.empty()) {
		pos_este = 0;

		for (int i=pos_este+1; i<nube.size(); ++i) {
			if (nube[i].x > nube[pos_este].x)
				pos_este = i;
		}
	}

	return pos_este;
}

int VariacionDistancia(const vector<vector<int>> &matriz_adyacencia,
                       const Arco &arco, int ind_ciudad) {
	int variacion = 0;

	int dist_original = arco.distancia;
	int dist_inicio_nuevo = matriz_adyacencia[arco.ind_inicial][ind_ciudad];
	int dist_nuevo_final = matriz_adyacencia[ind_ciudad][arco.ind_final];

	variacion = dist_inicio_nuevo + dist_nuevo_final - dist_original;

	return variacion;
}

InsercionCandidata InsercionEconomica(const vector<vector<int>> &matriz_adyacencia,
		         const vector<Arco> &ciclo, int ind_ciudad) {
	InsercionCandidata candidata(ind_ciudad);

	if (!ciclo.empty()) {
		int total = ciclo.size();
		candidata.ind_insercion = 0;
		candidata.variacion = VariacionDistancia(matriz_adyacencia,
                              ciclo[candidata.ind_insercion], ind_ciudad);

		for (int i=candidata.ind_insercion+1; i<total; ++i) {
			int nueva_variacion=VariacionDistancia(matriz_adyacencia,
					                               ciclo[i],ind_ciudad);

			if (nueva_variacion < candidata.variacion) {
				candidata.ind_insercion = i;
				candidata.variacion = nueva_variacion;

			}
		}
	}
	return candidata;
}

InsercionCandidata CiudadEconomica(const vector<vector<int>> &matriz_adyacencia,
		               const vector<Arco> &ciclo, const vector<bool> &banderas) {
	InsercionCandidata candidata;

	int ind_economico = 0;

	while (banderas[ind_economico] && ind_economico < banderas.size())
		++ind_economico;

	candidata = InsercionEconomica(matriz_adyacencia, ciclo, ind_economico);

	for (int i=ind_economico+1; i<matriz_adyacencia.size(); ++i) {
		if (!banderas[i]) {
			InsercionCandidata nueva = InsercionEconomica(matriz_adyacencia,ciclo,i);

			if (nueva.variacion < candidata.variacion) {
				candidata = nueva;

			}
		}
	}

	return candidata;
}

vector<Arco> CicloInsercionEconomica(const vector<vector<int>> &matriz_adyacencia,
               const vector<Punto2D> &distancias) {
	int total = matriz_adyacencia.size();

	vector<Arco> ciclo;
	vector<bool> banderas(total, false);
	vector<int> ind_iniciales;

	ind_iniciales.push_back(IndPuntoEste(distancias));
	ind_iniciales.push_back(IndPuntoOeste(distancias));
	ind_iniciales.push_back(IndPuntoNorte(distancias));

	int tam_inicial = ind_iniciales.size();

	for (int i=0; i<tam_inicial; ++i) {
		int pos_ini = ind_iniciales[i];
		int pos_fin = ind_iniciales[(i+1)%tam_inicial];

		ciclo.push_back(Arco(pos_ini, pos_fin,
						DistanciaEuclidea(distancias[pos_ini], distancias[pos_fin])));
	}

	for (int i=0; i<tam_inicial; ++i) {
		banderas[ind_iniciales[i]] = true;
	}

	for (int i=3; i<total; ++i) {
		InsercionCandidata nueva = CiudadEconomica(matriz_adyacencia, ciclo, banderas);

		if (nueva.ind_ciudad >= 0) {
			int ind_intermedio = nueva.ind_ciudad;
			int pos_insercion = nueva.ind_insercion;
			Arco cam_quitado = ciclo[pos_insercion];

			int ind_inicial = cam_quitado.ind_inicial;
			int ind_final = cam_quitado.ind_final;

			int dist_izq = DistanciaEuclidea(distancias[ind_inicial], distancias[ind_intermedio]);
			int dist_der = DistanciaEuclidea(distancias[ind_intermedio], distancias[ind_final]);

			Arco cam_nuevo_izq = Arco(ind_inicial, ind_intermedio, dist_izq);
			Arco cam_nuevo_der = Arco(ind_intermedio, ind_final, dist_der);

			ciclo.erase(ciclo.begin()+pos_insercion);
			ciclo.insert(ciclo.begin()+pos_insercion, cam_nuevo_der);
			ciclo.insert(ciclo.begin()+pos_insercion, cam_nuevo_izq);

			banderas[ind_intermedio] = true;
		}
	}

	return ciclo;
}

int main(int argc, char **argv) {

	if (argc < 2) {
		cerr << "Formato: ./program [1|2|3]";
	}

	clock_t tantes;    // Valor del reloj antes de la ejecución
  	clock_t tdespues;  // Valor del reloj después de la ejecución
	int dim;					// Entrada
	vector<Punto2D> distancias;	// Entrada
	int option;					// Entrada
	vector<Arco> ciclo;		// Salida
	double tiempo;	// Salida

	// Entrada de datos

	option = atoi(argv[1]);

	string cad;

	cin >> cad;	// Para no considerar la cadena "DIMENSION: "
	cin >> dim;

	for (int i=0; i<dim; ++i) {
		double pos_x, pos_y;

		cin >> cad; // Evitamos posicion
		cin >> pos_x;
		cin >> pos_y;

		distancias.push_back(Punto2D(pos_x,pos_y));
	}

	// Operaciones

	vector<vector<int>> ady;

	switch(option) {
		case 1:
			ady = CalculaMatrizAdyacencia(distancias);
			tantes = clock();
			ciclo = CicloVecinoMasCercano(ady);
			tdespues = clock();
			break;
		case 2:
			ady = CalculaMatrizAdyacencia(distancias);
			tantes = clock();
			ciclo = CicloInsercionEconomica(ady, distancias);
			tdespues = clock();
			break;
		default:
			cerr << "Parámetro no válido.\n";
			exit(-1);
			break;
	}

	tiempo = (double)(tdespues-tantes)/CLOCKS_PER_SEC*1000000;

	cout << "Inicio -> Final" << " : " << "Distancia recorrida" << endl;

	for (int i=0; i<ciclo.size(); ++i) {
		int ind_inicio = ciclo[i].ind_inicial;
		int ind_final = ciclo[i].ind_final;
		Punto2D inicio = distancias[ind_inicio];
		Punto2D final = distancias[ind_final];
		cout << "(" << inicio.x << ", " << inicio.y << ")" << " -> " 
			 << "(" << final.x << ", " << final.y << ")"
			 << " : " << ciclo[i].distancia << " ud" << endl;
	}

	cout << "Distancia total: " << DistanciaTotal(ciclo) << " ud" << endl << endl;

	cout << "Recorrido en coordenadas: " << endl;

	for (int i=0; i<ciclo.size(); ++i) {
		int ind = ciclo[i].ind_inicial;
		Punto2D punto = distancias[ind];
		cout << punto.x << " " << punto.y << endl;
	}

	cout << distancias[ciclo[0].ind_inicial].x << " " << distancias[ciclo[0].ind_inicial].y << endl;

	cout << "Tiempo consumido: " << tiempo << " μs\n";

	return 0;
}
