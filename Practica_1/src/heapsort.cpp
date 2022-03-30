/**
   @file Ordenación por montones
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <cmath>





/* ************************************************************ */ 
/*  Método de ordenación por montones  */

/**
   @brief Ordena un vector por el método de montones.
   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.
   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de ordenación por montones.
*/
inline static 
void heapsort(int T[], int num_elem);



/**
   @brief Reajusta parte de un vector para que sea un montón.
   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: número de elementos. num_elem > 0.
   @param k: índice del elemento que se toma com raíz
   
   Reajusta los elementos entre las posiciones k y num_elem - 1 
   de T para que cumpla la propiedad de un montón (APO), 
   considerando al elemento en la posición k como la raíz.
*/
static void reajustar(int T[], int num_elem, int k);




/**
   Implementación de las funciones
**/


static void heapsort(int T[], int num_elem)
{
  int i;
  for (i = num_elem/2; i >= 0; i--)
    reajustar(T, num_elem, i);
  for (i = num_elem - 1; i >= 1; i--)
    {
      int aux = T[0];
      T[0] = T[i];
      T[i] = aux;
      reajustar(T, i, 0);
    }
}
  

static void reajustar(int T[], int num_elem, int k)
{
  int j;
  int v;
  v = T[k];
  bool esAPO = false;
  while ((k < num_elem/2) && !esAPO)
    {
      j = k + k + 1;
      if ((j < (num_elem - 1)) && (T[j] < T[j+1]))
	j++;
      if (v >= T[j])
	esAPO = true;
      T[k] = T[j];
      k = j;
    }
  T[k] = v;
}
  
      
int main(int argc,char* argv[])
{

  const int MAX_VECTOR = 50;

  clock_t tantes;    // Valor del reloj antes de la ejecución
  clock_t tdespues;  // Valor del reloj después de la ejecución
  int n = stoi(argv[1]);

  int *T[MAX_VECTOR];
  
  for (int i=0; i<MAX_VECTOR; ++i)
    T[i] = new int[n];

  srandom(time(0));

  for (int k=0; k<MAX_VECTOR; ++k)
    for (int i = 0; i < n; i++)
      T[k][i] = random();

  // escribe_vector(T, n);
  
  int num_repetitions = max(1,MAX_VECTOR - n/20000);

  tantes = clock();
  
  for (int i=0; i<num_repetitions; ++i)
    heapsort(T[i], n);
    
  tdespues = clock();
  cout << ((double)(tdespues-tantes)/num_repetitions)/(CLOCKS_PER_SEC*10E-6) << endl;

  // escribe_vector(T, n);

  for (int i=0; i<MAX_VECTOR; ++i)
    delete [] T[i];

  return 0;
};
