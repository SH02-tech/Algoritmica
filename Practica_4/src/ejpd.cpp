#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

const int TO_PORC = 100;

double simil(string cad_h1,string cad_h2){

	if (cad_h1.length() == cad_h2.length()){
		int cont_simil = 0;

		for (int i = 0 ; i < cad_h1.length(); ++i){
			if(cad_h1[i] == cad_h2[i]){
				++cont_simil;
			}
		}
		return ((double) cont_simil/cad_h1.length()) * TO_PORC;
	}
	else{
		return 0;
	}
}

int main(int argc, char *argv[]){

	vector<char> v;
	string cad_h1,cad_h2;
	
	if(argc < 2){
		cout << "Número de argumentos no válidos."<<endl;
		exit(1);
	}

	ifstream fe(argv[1]);

	fe >> cad_h1;
	fe >> cad_h2;

		cout << "Estudio del ADN entre 2 hermanos: " << endl;
	cout << "Cadena de ADN del hermano 1: " << cad_h1 << endl;
	cout << "Cadena de ADN del hermano 2: " << cad_h2 << endl;
	cout << "Porcentaje de simulitud entre ambos hermanos: " << simil(cad_h1,cad_h2)<<endl;

	return 0;	
}

