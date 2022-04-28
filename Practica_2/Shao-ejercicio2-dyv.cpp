#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define NULL_POS -1

int FindPosMin(const vector<vector<int>::const_iterator> &vect) {
	int pos = NULL_POS;

	if (!vect.empty()) {
		pos = 0;

		for (int i=pos+1; i<vect.size(); ++i) {
		if (*(vect[pos]) > *(vect[i]))
			pos = i;
		}
	}

	return pos;
}

vector<int> Agrupa(vector<vector<int>> vectores) {
	int pos;
	vector<int> acumulador;
	vector<vector<int>::const_iterator> it_vectors(vectores.size());

	for (int i=0; i<vectores.size(); ++i)
		it_vectors[i] = vectores[i].begin();

	while (!it_vectors.empty()) {
		pos = FindPosMin(it_vectors);

		acumulador.push_back(*(it_vectors[pos]));
		++it_vectors[pos];

		if (it_vectors[pos] == vectores[pos].end()) {
			it_vectors.erase(it_vectors.begin()+pos);
			vectores.erase(vectores.begin()+pos);
		}
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
