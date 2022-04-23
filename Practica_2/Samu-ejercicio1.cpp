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

// Algoritmo que busca el punto fijo de vectores ordenados ascendentemente.

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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int NULL_POS = -1;
const int UMBRAL = 2; 
const int REPETITIONS = 50;
const int SIZE_VECTOR = 20000;


int Obvious(vector<int> v,int init,int fin){
   
    int pos = NULL_POS;

    for(int i=init;i<fin && pos!=NULL_POS;++i){
        if(v[i]==i){
            pos = i;
        }
    }

    return pos;
}

int IqualElement(vector<int> v,int init,int fin){

    int pos = NULL_POS;
    int mid=(fin-init)/2;

    if((fin-init+1)<=UMBRAL){
        return Obvious(v,init,fin);
    }
    else{
        
        if(v[mid]>mid){
            return IqualElement(v,init,mid-1);
        }
        else if(v[mid]<mid){
            return IqualElement(v,mid+1,fin);
        }
        else{
            pos=mid;
        }
    }
    return pos;
}



int main(int argc, char * argv[]) {
    

	if (argc !=2) {
	cerr << "Formato: " << argv[0] << " <num_elem> " << endl;
	return -1;
	}

	int n = atoi(argv[1]);

	static int time = 0;
	static chrono::_V2::steady_clock::time_point tantes;    // Valor del reloj antes de la ejecución
	static chrono::_V2::steady_clock::time_point tdespues;  // Valor del reloj antes de la ejecución
	static vector<int> v(n);

	
	v = vectorGenerator(n);

	tantes = chrono::steady_clock::now();    // Valor del reloj antes de la ejecución
	IqualElement(v, 0, n-1);
	tdespues = chrono::steady_clock::now();    // Valor del reloj antes de la ejecución

	time = chrono::duration_cast<chrono::nanoseconds>(tdespues - tantes).count();


	cout << time << endl; // Tiempo en nanosegundos. 

    return 0;
}
