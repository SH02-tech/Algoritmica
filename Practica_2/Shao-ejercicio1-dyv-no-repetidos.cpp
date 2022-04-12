#include <iostream>
#include <vector>
using namespace std;

#define UMBRAL 2
#define NULL_POS -1

int PosTipoICTrivial(const vector<int> &v, int inicial, int final) {
	int pos = NULL_POS;

	for (int i=inicial; i<=final && pos == NULL_POS; ++i)
		if (v[i] == i)
			pos = i;

	return pos;
}

int PosTipoIC(const vector<int> &v, int inicial, int final) {
	int pos = NULL_POS;
	
	if ((final - inicial + 1) < UMBRAL)
		pos = PosTipoICTrivial(v, inicial, final);
	else {
		int media = (inicial+final)/2;
		int aux = NULL_POS;

		if (v[media] < media)
			aux = PosTipoIC(v, media+1, final);
		else if (v[media] > media)
			aux = PosTipoIC(v, inicial, media-1);
		else
			aux = media;

		if (aux != NULL_POS)
			pos = aux;
	}
	return pos;
}

int main(int argc, char **argv) {
	vector<int> vect;
	
	for (int i=1; i<argc; ++i)
		vect.push_back(atoi(argv[i]));

	for (int i=0; i<vect.size(); ++i)
		cout << vect[i] << " ";

	cout << endl;

	int pos = PosTipoIC(vect, 0, vect.size()-1); 
	
	if (pos != NULL_POS)
		cout << "Es tipo IC, con pos " << pos << ".\n";
	else
		cout << "No es tipo IC.\n";

	return 0;
}
