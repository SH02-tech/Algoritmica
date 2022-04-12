#include <iostream>
#include <vector>
using namespace std;

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

	vector<int> v1(5), v2(7), v3(6);

	for (int i=0; i<v1.size(); ++i)
		v1[i] = i;

	for (int i=0; i<v2.size(); ++i)
		v2[i] = i+2;
	
	for (int i=0; i<v3.size(); ++i)
  		v3[i] = i+6;


	list<vector<int>> lista_vectores;

	lista_vectores.push_back(v1);
	lista_vectores.push_back(v2);
	lista_vectores.push_back(v3);
	vector<int> acumulador = Agrupa(lista_vectores); 

	for (int i=0; i<acumulador.size(); ++i)
		cout << acumulador[i] << " ";

	cout << endl;

	return 0;
}
