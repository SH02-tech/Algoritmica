#include <iostream>
#include <fstream>
#include "grafo.h"
#include <iomanip>
#include <math.h>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Heurística basada en la idea del algoritmo de Kruskal
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Dado un nodo origen, un nodo destino, un grafo devuelve si existe camino 
 * entre un nodo y otro. TEMPLATE.
 * @param org puntero al nodo origen
 * @param dest puntero al nodo destino
 * @param G grafo
 * @return true si existe camino, false en caso contrario
 */
template <class Tn,class Ta>
bool camino(nodo<Tn,Ta>* org, nodo<Tn,Ta>* dest, grafo<Tn,Ta> & G){

    bool enc=0;
    arco<Tn,Ta> *ar;
    typename nodo<Tn,Ta>::arcoIterator a;

    if ((ar=G.buscarArco(org,dest))) {
        return true;
    }
    else{
        for (a = org->abegin(); a!= org->aend() && !enc ; ){
            if (camino( a->nodoDestino(),dest,G)){
                enc=true;
            }
            else
                ++a;
        }
        return enc;
    }
}

/**
 * @brief Comprueba que no existan ciclos en el grafo
 * @param g grafo
 * @pre grafo sin lazos (clclo entre un nodo y el mismo)
 * @return true si se cumple que no hay ciclos, false en otro caso
 */
bool sinCiclos(grafo<int,int> & g) {

    // La idea es la siguiente, vamos a ir comprobando si hay caminos entre un 
    // nodo y el mismo en el grafo solucion (sabemos que no hay lazos) luego si
    // existe camino, sabemos que hay un ciclo, luego el grafo tiene ciclos,
    // y si no hay para ninguno pues el grafo no tiene ciclos y es admisible.

    int indiceNodo;
    nodo<int,int> * nodo;
    bool noHayCiclos = true;

    for(auto it = g.pbegin(); it != g.pend() && noHayCiclos; ++it) {

        indiceNodo = (*it).indice();
        nodo = g.buscarNodoConIndice(indiceNodo);

        if (camino(nodo, nodo, g)) {
            noHayCiclos = false;
        }
    }

    return noHayCiclos;
}

/**
 * @brief Inicializa un grafo sin arcos de nNodos nodos a partir de g
 * @param nNodos número de nodos a crear en el grafo
 */
void grafoSinArcos(int nNodos, grafo<int,int> & g) {
    if (nNodos > 0) {
        for (int i = 0; i < nNodos; ++i) {
            g.insertarNodo(i);  // Etiquetamos con números enteros
        }
    }
}

/**
 * @brief Dados dos nodos comprueban que cumplen las condiciones necesarias
 * para formar un arco entre ellos.
 * @param nodoOrigen 
 * @param nodoDestino
 * @return true si se cumple la condición, false en otro caso
 */
bool nodosCorrectos(nodo<int,int> * nodoOrigen, nodo<int,int> * nodoDestino) {
    return (nodoOrigen->getNArcosInc() <= 1 && nodoOrigen->getNArcosAdy() == 0) &&
    (nodoDestino->getNArcosAdy() <= 1 && nodoDestino->getNArcosInc() == 0);
}

/**
 * @brief Funcion que calcula el circuito hamiltoniano que resuelve el PVC
 * @param arcos arcos ordenados del grafo en orden creciente
 * @pre el parametro arcos no contiene lazos (ciclos entre un nodo y el mismo)
 * @param nNodos numero de nodos del grafo
 * @return grafo con el circuito hamiltoniano solución del problema
 */
void resuelvePVC(list<arco<int,int>> & arcos, int nNodos, grafo<int,int> & solucion) {

    grafoSinArcos(nNodos, solucion);
    arco<int,int> arcoCandidato;
    int nArcosInsertados = 0;
    int indiceOrigen, indiceDestino, ponderacion;
    nodo<int,int> * nodoOrigen, * nodoDestino;

    while (nArcosInsertados < nNodos && !arcos.empty()) {

        arcoCandidato = arcos.front();   // Seleccionamos el arco de menor valor
        arcos.pop_front();  // Borramos el arco del conjunto de candidatos

        // Extraemos los datos del arcoCandidato
        indiceOrigen = arcoCandidato.nodoOrigen()->indice();
        indiceDestino = arcoCandidato.nodoDestino()->indice();
        ponderacion = arcoCandidato.etiqueta();
        nodoOrigen = solucion.buscarNodoConIndice(indiceOrigen);
        nodoDestino = solucion.buscarNodoConIndice(indiceDestino);

        // Si se inserta el último arco solo comprobamos la condición del grado
        if (nArcosInsertados == nNodos-1) {
            if (nodosCorrectos(nodoOrigen, nodoDestino)) {
                solucion.insertarArco(nodoOrigen, nodoDestino, ponderacion);
                nArcosInsertados++;
            }
        } else {    // En este caso comprobamos tambien la condición de conexión sin ciclos
            if (nodosCorrectos(nodoOrigen, nodoDestino)) {
                solucion.insertarArco(nodoOrigen, nodoDestino, ponderacion);
                if (sinCiclos(solucion)) {
                    nArcosInsertados++;
                } else {
                    // Debemos de quitar la insercion anterior.
                    // Primero quitamos el arco origen->insertarAdy(destino, valor)
                    // Segundo quitamos el arco destino->insertarInc(origen, valor)
                    nodoOrigen->borrarAdy(--nodoOrigen->aend());
                    nodoDestino->borrarInc(--nodoDestino->iend());
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Algunas funciones para el procesado de datos

struct Punto2D {
    double x;
    double y;

    Punto2D(double pos_x, double pos_y) :x(pos_x), y(pos_y) {}
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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Algunas funciones auxiliares para el grafo

template<class Tn,class Ta>
void Presentar_Grafo(grafo<Tn,Ta>& G){
    typename grafo<Tn,Ta>::nodoIterator n;
    typename nodo<Tn,Ta>::arcoIterator a;

    for (n=G.nbegin(); n!=G.nend() ; ++n){
        cout << n->etiqueta()<<"->\n";
        for (a=n->abegin(); a!=n->aend() ; ++a){
            cout << "   " <<a->nodoDestino()->etiqueta()
                 << " : " << a->etiqueta() << endl;
        }
    }
}

template<class Tn,class Ta>
vector<Punto2D> ImprimirCiclo(grafo<Tn,Ta> &graf, const vector<Punto2D> &ciudades) {
    vector<Punto2D> posiciones;

    typename grafo<Tn,Ta>::nodoIterator n = graf.nbegin();
    typename nodo<Tn,Ta>::arcoIterator a = n->abegin();

    int comienzo = n->etiqueta();
    int siguiente = a->nodoDestino()->etiqueta();

    posiciones.push_back(ciudades[comienzo]);

    while (siguiente != comienzo) {
        posiciones.push_back(ciudades[siguiente]);

        // Actualizamos
        ++n;
        a = n->abegin();
        siguiente = a->nodoDestino()->etiqueta();
    }

    posiciones.push_back(ciudades[comienzo]);

    return posiciones;
}

template <class Tn, class Ta>
void Presentar_Incidentes(nodo<Tn,Ta> * n){

    typename nodo<Tn,Ta>::arcoIterator i;

    cout <<"Listado de Incidentes\n";
    for ( i = n->ibegin(); i != n->iend() ; i++ ){
        cout << n->etiqueta();
        cout << i->nodoDestino()->etiqueta();
        cout << i->etqArco() << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv) {

    ///////////////////////////////////////////////////////////////////////////
    // Lectura de datos

    // Declaraciones

    ifstream fi;
    string root = argv[1];
    int nNodos;
    vector<Punto2D> distancias;
    string cad;

    // Entrada

    fi.open(root);

    fi >> cad;     // Para ignorar "DIMENSION"
    fi >> nNodos;

    for (int i=0; i<nNodos; ++i) {
        double pos_x, pos_y;
        fi >> cad;     // Para ignorar la posicion
        fi >> pos_x;
        fi >> pos_y;
        distancias.push_back(Punto2D(pos_x,pos_y));
    }

    fi.close();

    vector<vector<int>> mAdyacencia = CalculaMatrizAdyacencia(distancias);

    ///////////////////////////////////////////////////////////////////////////
    // Creacion del grafo y de la lista ordenada de arcos
    // La lista ordenada de arcos no contendra lazos (arcos entre un nodo y el mismo).

    grafo<int, int> G;
    list<arco<int,int>> arcos;
    nodo<int,int> * nodo1, * nodo2;
    arco<int,int> arcoAuxiliar;
    for (int i = 0; i < nNodos; ++i) {
        G.insertarNodo(i);
    }

    for (int i = 0; i < nNodos; ++i) {
        for (int j = 0; j < nNodos; ++j) {
            nodo1 = G.buscarNodo(i);
            nodo2 = G.buscarNodo(j);
            G.insertarArco(nodo1, nodo2, mAdyacencia[i][j]);
            if (nodo1->indice() != nodo2->indice()) {   // Evitamos lazos
                arco<int,int> arcoAuxiliar(nodo1, nodo2, mAdyacencia[i][j]);
                arcos.push_back(arcoAuxiliar);
            }
        }
    }

    // Ahora trataremos de ordenar la arista en funcion de la ponderacion del arco

    arcos.sort();

    // Presentamos el grafo creado y la lista de arcos

    Presentar_Grafo(G);

    cout << endl;
    cout << "Valores de los arcos:" << endl;
    for (auto it = arcos.begin(); it != arcos.end(); ++it) {
        cout << it->etiqueta() << ", ";
    }
    cout << endl;

    ///////////////////////////////////////////////////////////////////////////
    // Calculos para resolver el PVC

    grafo<int,int> hamiltoniano;
    resuelvePVC(arcos, G.size(), hamiltoniano);

    cout << endl;

    Presentar_Grafo(hamiltoniano);

    cout << endl << endl;

    vector<Punto2D> indicesCamino = ImprimirCiclo(hamiltoniano, distancias);

    cout << "Matriz de adyacencia: " << endl;

    for(int i=0; i < mAdyacencia.size(); i++) {
        for(int j=0; j < mAdyacencia[0].size(); j++) {
            cout << setw(3) << mAdyacencia[i][j];
        }
        cout << endl;
    }

    cout << "Camino: " << endl;

    for (int i=0; i<indicesCamino.size(); ++i) {
        Punto2D ciudad = indicesCamino[i];
        cout << ciudad.x << " " << ciudad.y << endl;
    }

    cout << endl;

    // Calculamos la distanciaTotal del grafo

    double distanciaTotal = 0;

    cout << "Distancias: ";

    for (auto it = hamiltoniano.nbegin(); it != hamiltoniano.nend(); ++it) {
        cout << (*(*it).abegin()).etiqueta() << " ";
        distanciaTotal += (*(*it).abegin()).etiqueta();
    }

    cout << "\nDistancia total: " << distanciaTotal << endl;

    return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
