#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>

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

void MergeSortedIntervals(vector<int>& v, int s, int m, int e) {
	
    // temp is used to temporary store the vector obtained by merging
    // elements from [s to m] and [m+1 to e] in v
	vector<int> temp;

	int i, j;
	i = s;
	j = m + 1;

	while (i <= m && j <= e) {

		if (v[i] <= v[j]) {
			temp.push_back(v[i]);
			++i;
		}
		else {
			temp.push_back(v[j]);
			++j;
		}

	}

	while (i <= m) {
		temp.push_back(v[i]);
		++i;
	}

	while (j <= e) {
		temp.push_back(v[j]);
		++j;
	}

	for (int i = s; i <= e; ++i)
		v[i] = temp[i - s];

}

// the MergeSort function
// Sorts the array in the range [s to e] in v using
// merge sort algorithm
void MergeSort(vector<int>& v, int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		MergeSort(v, s, m);
		MergeSort(v, m + 1, e);
		MergeSortedIntervals(v, s, m, e);
	}
}

int FindPosMin(const vector<vector<int>::const_iterator> &it_vect, const vector<vector<int>> &vect) {
	int pos = NULL_POS;

	for (int i=0; i<it_vect.size() && pos == NULL_POS; ++i) {
		if (it_vect[i] != vect[i].end())
			pos = i;
	}

	if (pos != NULL_POS) {
		for (int i=pos+1; i<vect.size(); ++i) {
			if (*(it_vect[pos]) > *(it_vect[i]) && it_vect[pos] != vect[pos].end())
				pos = i;
		}
	}

	return pos;
}

vector<int> Agrupa(const vector<vector<int>> &vectores) {
	int pos;
	vector<int> acumulador;
	vector<vector<int>::const_iterator> it_vectors(vectores.size());

	for (int i=0; i<vectores.size(); ++i)
		it_vectors[i] = vectores[i].begin();

	pos = FindPosMin(it_vectors, vectores);

	while (pos != NULL_POS) {

		cout << "Agregando " << *(it_vectors[pos]) << endl;

		acumulador.push_back(*(it_vectors[pos]));
		++it_vectors[pos];

		pos = FindPosMin(it_vectors, vectores);
	}

	return acumulador;
}

int main(int argc, char * argv[])
{

    int n=atoi(argv[1]);
    int k=atoi(argv[2]);

    vector<vector<int>> v;
    vector<int> v_uniq;

    v=vectorsGenerator(n,k);
    
    vector<vector<int>>::iterator it;
    vector<int>::iterator itv;

    for(it=v.begin();it!=v.end();++it){
        for(itv=(*it).begin();itv!=(*it).end();++itv){
            cout<<(*itv)<<" ";
            v_uniq.push_back(*itv);
        }
        cout<<endl;
    }
    
    cout<<endl;
    cout<<endl;
        
    MergeSort(v_uniq,0,k*n-1);

    vector<int>::iterator itu;

    for(itu=v_uniq.begin();itu!=v_uniq.end();++itu){
        cout<<(*itu)<<" ";
    }

    return 0;
}