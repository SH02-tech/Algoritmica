#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <iomanip>
using namespace std;

#define MAX 50

int main() {
    string palabra1;      // Entrada
    string palabra2;      // Entrada
    string subsecuencia;  // Salida
    int longitud_subsecuencia = 0; // Salida

    // ---------------------------------------------------- Entrada de datos

    cin >> palabra1 >> palabra2; 

    // ---------------------------------------------------- Operaciones

    int matriz[MAX][MAX] = {0};

    // Cálculo de la matriz

    for (int i=1; i<=palabra1.size(); ++i) {
        for (int j=1; j<=palabra2.size(); ++j) {
            if (palabra1[i-1] == palabra2[j-1]) {
                matriz[i][j] = matriz[i-1][j-1] + 1;
            } else {
                matriz[i][j] = max(matriz[i][j-1], matriz[i-1][j]);
            }
        }
    }

    longitud_subsecuencia = matriz[palabra1.size()][palabra2.size()];

    // Cálculo de la secuencia

    stack<char> sec_invertida;

    int pos_x = palabra1.size();
    int pos_y = palabra2.size();

    while (pos_x != 0 && pos_y != 0) {
        if (palabra1[pos_x-1] == palabra2[pos_y-1]) {
            sec_invertida.push(palabra1[pos_x-1]);
            --pos_x;
            --pos_y;
        } else {
            if (matriz[pos_x][pos_y-1] > matriz[pos_x-1][pos_y]) {
                --pos_y;
            } else {
                --pos_x;
            }
        }
    }

    while (!sec_invertida.empty()) {
        subsecuencia.push_back(sec_invertida.top());
        sec_invertida.pop();
    }

    // ---------------------------------------------------- Salida de datos

    cout << "Matriz obtenida: " << endl;

    for (int i=0; i<=palabra1.size(); ++i) {
        for (int j=0; j<=palabra2.size(); ++j) {
            cout << setw(5) << matriz[i][j];
        }
        cout << endl;
    }

    cout << subsecuencia << " (longitud " << longitud_subsecuencia << ")\n";
    cout << "Longitud total de las palabras: " << palabra1.size() << "\n";

    return 0;
}