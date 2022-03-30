#!/bin/bash
######################################################################
# Archive: MainGraphP1_mp.sh
# Parameters: Not necessary
# Return: Nothing
######################################################################

# Copy the scripts from ../GraphKiller, so we have them in the current directory of GraphP1.sh
cp ../GraphKiller/*.sh .

g++ -O3 src/insercion-mejor.cpp -o insercion-mejor
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en microsegundos)" --min-x 5 --max-x 45050 --num-points 25  --repetitions-per-point 5 insercion-mejor
rm insercion-mejor

g++ -O3 src/insercion-peor.cpp -o insercion-peor
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en microsegundos)" --min-x 5 --max-x 45050 --num-points 25  --repetitions-per-point 5 insercion-peor
rm insercion-peor

g++ -O3 src/seleccion-mejor.cpp -o seleccion-mejor
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en microsegundos)" --min-x 5 --max-x 45050 --num-points 25  --repetitions-per-point 5 seleccion-mejor
rm seleccion-mejor

g++ -O3 src/seleccion-peor.cpp -o seleccion-peor
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en microsegundos)" --min-x 5 --max-x 45050 --num-points 25  --repetitions-per-point 5 seleccion-peor
rm seleccion-peor

# Delete the scripts imported from ../GraphKiller.
rm {BestFitter,GraphPlotter,PointsPlotter,MainGraph,Regressions,TableGenerator}.sh

### END
