#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;

#define NULL_POS -1

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tama�o k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tama�o n para obtener los k vectores. Est�n ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
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

vector<int> Unifica(const vector<int> &vector1, const vector<int> &vector2) {
	vector<int> acumulador;
	vector<int>::const_iterator it_vector1 = vector1.begin(); 
	vector<int>::const_iterator it_vector2 = vector2.begin();

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

vector<int> mergedyv(const vector<vector<int>> & coleccion){

    int k = coleccion.size();
    vector<vector<int>> aux_coleccion;

    // Poner condición de umbral

    if (k == 1) {
        return coleccion[0];

    } else if (k > 1) {

        if (k % 2 == 0){  
            for (size_t i = 0; i < k/2; i+=2)
                aux_coleccion.push_back(Unifica(coleccion[i],coleccion[i+1]));

            return mergedyv(aux_coleccion);
        } else {
            for (size_t i = 0; i < (k-1)/2; i+=2)
                aux_coleccion.push_back(Unifica(coleccion[i],coleccion[i+1]));
    
            aux_coleccion.push_back(*(coleccion.end()-1));
            return mergedyv(aux_coleccion);
        }
    } 
}

////////////////////////////////////////////////////////////////////////////////////////

// Main para obtener datos de la eficiencia

#ifndef REPETITIONS
#define REPETITIONS 50
#endif

int main(int argc, char * argv[])
{

    if (argc !=2) {
        cerr << "Formato: " << argv[0] << " <num_vectores> <tamaño_vector>" << endl;
        return -1;
    }

    int k=atoi(argv[1]);
    int n=atoi(argv[2]);
   
    vector<vector<int>> v;
    vector<int> v_uniq, r;

    v = vectorsGenerator(n,k);
    
    // vector<vector<int>>::iterator it;
    // vector<int>::iterator itv;
    // for(it=v.begin();it!=v.end();++it){
    //     for(itv=(*it).begin();itv!=(*it).end();++itv){
    //         cout<<(*itv)<<" ";
    //         v_uniq.push_back(*itv);
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    // cout<<endl;
        
    static int acumulador = 0;
    static chrono::_V2::steady_clock::time_point tantes;    // Valor del reloj antes de la ejecución
    static chrono::_V2::steady_clock::time_point tdespues;  // Valor del reloj antes de la ejecución

    r = mergedyv(v);

    // vector<int>::iterator itu;
    // for(itu=r.begin();itu!=r.end();++itu){
    //     cout<<(*itu)<<" ";
    // }
    // cout << endl;

    return 0;
}