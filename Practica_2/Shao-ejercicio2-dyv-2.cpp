#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define NULL_POS -1

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

int main(int argc, char **argv) {

	vector<int> v1(5), v2(7), v3(6);

	for (int i=0; i<v1.size(); ++i)
		v1[i] = i;

	for (int i=0; i<v2.size(); ++i)
		v2[i] = i+2;
	
	for (int i=0; i<v3.size(); ++i)
  		v3[i] = i+6;


	vector<vector<int>> lista_vectores;

	lista_vectores.push_back(v1);
	lista_vectores.push_back(v2);
	lista_vectores.push_back(v3);
	vector<int> acumulador = Agrupa(lista_vectores); 

	for (int i=0; i<acumulador.size(); ++i)
		cout << acumulador[i] << " ";

	cout << endl;

	return 0;
}
