/**
   @file Ordenaci�n por selecci�n
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>






/* ************************************************************ */ 
/*  M�todo de ordenaci�n por selecci�n  */

/**
   @brief Ordena un vector por el m�todo de selecci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de selecci�n.
*/
inline static 
void seleccion(int T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo de selecci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de selecci�n.
*/
static void seleccion_lims(int T[], int inicial, int final);



/**
   Implementaci�n de las funciones
**/

void seleccion(int T[], int num_elem)
{
  seleccion_lims(T, 0, num_elem);
}

static void seleccion_lims(int T[], int inicial, int final)
{
  int i, j, indice_menor;
  int menor, aux;
  for (i = inicial; i < final - 1; i++) {
    indice_menor = i;
    menor = T[i];
    for (j = i; j < final; j++)
      if (T[j] < menor) {
	indice_menor = j;
	menor = T[j];
      }
    aux = T[i];
    T[i] = T[indice_menor];
    T[indice_menor] = aux;
  };
}



int main(int argc, char * argv[])
{
  const int MAX_VECTOR = 60;
  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);

  int *T[MAX_VECTOR];
  
  for (int i=0; i<MAX_VECTOR; ++i)
    T[i] = new int[n];
  assert(T);

  srandom(time(0));

  for (int k=0; k<MAX_VECTOR; ++k)
    for (int i = 0; i < n; i++)
      T[k][i] = random();


  const int TAM_GRANDE = 2000;
  const int NUM_VECES = 100;

  int num_repetitions = max(1,MAX_VECTOR - n/20000);

  clock_t t_antes = clock();
  
  
  for (int i=0; i<num_repetitions; ++i)
    seleccion(T[i], n);
  
  clock_t t_despues = clock();

  cout << ((double)(t_despues - t_antes)/num_repetitions) / (CLOCKS_PER_SEC*10E-6) << endl;

  for (int i=0; i<MAX_VECTOR; ++i)
    delete [] T[i];

  return 0;
};
