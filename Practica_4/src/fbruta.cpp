#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <iomanip>
#include <string>
#include <chrono>
#define MAX_BASE 16
using namespace std;


vector<int> Base10ToN (int data, int base) {
    string num_n;
    vector<int> solution;

    if (0 < base && base <= MAX_BASE) {
        stack<int> digits;

        // Almacenamos los restos de dividir entre la base.

        do {
            int digit = data%base;
            digits.push(digit);

            data /= base;
        } while (data > 0);

        // Introducimos los restos transformándolo en la base de destino.

        while (!digits.empty()) {
            int digit = digits.top();
            digits.pop();

            solution.push_back(digit);
        }
    }

    return solution;
}

void subcadenasPalabra(vector<string> & subcadenas, const string &palabra) {

    subcadenas.clear();
    subcadenas.push_back("");

    int contador = 0;

    int total = pow(2, palabra.size());

    for (int i=1; i<total; ++i) {
        string subcadena;
        vector<int> num_bin = Base10ToN(i, 2);

        if (num_bin.size() < palabra.size()) {
            vector<int> vectNul(palabra.size()-num_bin.size(), 0);
            num_bin.insert(num_bin.begin(), vectNul.begin(), vectNul.end());
        }

        for (int j=0; j<palabra.size(); ++j) {
            if (num_bin[j] == 1) {
                subcadena.push_back(palabra[j]);
            }
        }
        subcadenas.push_back(subcadena);
    }

}

string buscaSubcadenaMasLarga(const vector<string> & subcadenas1, const vector<string> & subcadenas2) {

    int longitudSubcadenas1 = subcadenas1.size();
    int longitudSubcadenas2 = subcadenas2.size();

    string subcadenaMasLarga = "";
    int longitudSubcadenaMasLarga = 0;

    for (int i = 0; i < longitudSubcadenas1; i++)
    {
        for (int j = 0; j < longitudSubcadenas2; j++)
        {
            if (subcadenas1[i] == subcadenas2[j] && subcadenas1[i].size() > longitudSubcadenaMasLarga) {
                subcadenaMasLarga = subcadenas1[i];
                longitudSubcadenaMasLarga = subcadenas1[i].size();
            }
        }
    }
    
    return subcadenaMasLarga;
}

int main() {

    string palabra1;      // Entrada
    string palabra2;      // Entrada
    string subsecuenciaMasLarga;  // Salida

    vector<string> subcadenasPalabra1;
    vector<string> subcadenasPalabra2;

    clock_t tantes;    // Valor del reloj antes de la ejecución
	clock_t tdespues;  // Valor del reloj después de la ejecución
    
    // ---------------------------------------------------- Entrada de datos

    cin >> palabra1 >> palabra2; 

    // ---------------------------------------------------- Operaciones

    tantes = clock();

    subcadenasPalabra(subcadenasPalabra1, palabra1);
    subcadenasPalabra(subcadenasPalabra2, palabra2);

    subsecuenciaMasLarga = buscaSubcadenaMasLarga(subcadenasPalabra1, subcadenasPalabra2);

    tdespues = clock();

    // // ---------------------------------------------------- Salida

    cout << subsecuenciaMasLarga << " (longitud " << subsecuenciaMasLarga.size() << ")\n";
    cout << "Longitud total de las palabras: " << palabra1.size() << "\n";

    cout << "Tiempo: " << ((double)(tdespues-tantes))/(CLOCKS_PER_SEC*1E-3) << " ms" << endl; // Tiempo en milisegundos. 

    return 0;
}

