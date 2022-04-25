#!/bin/bash
######################################################################
# Archive: MainGraph.sh
# It pass all the necessaru to the MainGraph
# Parameters: Not necessary
# Return: Nothing
######################################################################

# Copy the scripts from ../GraphKiller, so we have them in the current directory of GraphP2.sh
cp ../GraphKiller/*.sh .

g++ -O3 src/ejercicio-1-comp-fija-no-repetidos.cpp -o ejercicio-1-comp-fija-no-repetidos
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en nanosegundos)" --min-x 1 --max-x 1001 --num-points 20  --repetitions-per-point 1 ejercicio-1-comp-fija-no-repetidos
rm ejercicio-1-comp-fija-no-repetidos

g++ -O3 src/ejercicio-1-comp-fija-repetidos.cpp -o ejercicio-1-comp-fija-repetidos
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 1 --max-x 1001 --num-points 20  --repetitions-per-point 20 ejercicio-1-comp-fija-repetidos
rm ejercicio-1-comp-fija-repetidos

g++ -O3 src/ejercicio-2-mezcla.cpp -o ejercicio-2-mezcla
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 1 --max-x 1001 --num-points 20  --repetitions-per-point 20 ejercicio-2-mezcla
rm ejercicio-2-mezcla

#g++ -O3 src/seleccion-peor.cpp -o seleccion-peor
#./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en nanosegundos)" --min-x #1 --max-x 45050 --num-points 25  --repetitions-per-point 1 seleccion-peor
#rm seleccion-peor

# Delete the scripts imported from ../GraphKiller.
rm {BestFitter,GraphPlotter,PointsPlotter,MainGraph,Regressions,TableGenerator}.sh

### END
