#!/bin/bash
######################################################################
# Archive: MainGraph.sh
# It pass all the necessaru to the MainGraph
# Parameters: Not necessary
# Return: Nothing
######################################################################

REPETICIONES=30

# Copy the scripts from ../GraphKiller, so we have them in the current directory of GraphP2.sh
cp ../GraphKiller/*.sh .

# GRUPO 1
g++ src/ejercicio-1-comp-fija-repetidos.cpp -o ejercicio-1-comp-fija-repetidos-comparado
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 1 --max-x 21 --num-points 10  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-repetidos-comparado
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 25 --max-x 1000 --num-points 39  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-repetidos-comparado
rm ejercicio-1-comp-fija-repetidos-comparado

# GRUPO 2
g++ src/ejercicio-1-comp-fija-repetidos.cpp -o ejercicio-1-comp-fija-repetidos
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 1 --max-x 2 --num-points 1  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-repetidos
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 250000 --max-x 10000000 --num-points 39  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-repetidos
rm ejercicio-1-comp-fija-repetidos

# GRUPO 3
g++ src/ejercicio-1-comp-fija-repetidos.cpp -D UMBRAL=1000000000 -o ejercicio-1-comp-fija-repetidos-lineal
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 1 --max-x 2 --num-points 1  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-repetidos-lineal
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 250000 --max-x 10000000 --num-points 39  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-repetidos-lineal
rm ejercicio-1-comp-fija-repetidos

# GRUPO 4
g++ src/ejercicio-2-mezcla.cpp -o ejercicio-2-mezcla-n
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 1 --max-x 2 --num-points 1  --repetitions-per-point $REPETICIONES ejercicio-2-mezcla-n
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en milisegundos)" --min-x 250000 --max-x 10000000 --num-points 39  --repetitions-per-point $REPETICIONES ejercicio-2-mezcla-n
rm ejercicio-2-mezcla-n

# GRUPO 5
g++ -D KELEMENTS src/ejercicio-2-mezcla.cpp -o ejercicio-2-mezcla-k
./MainGraph.sh --xlabel "Número de vectores" --ylabel "Tiempo (en milisegundos)" --min-x 1 --max-x 2 --num-points 1  --repetitions-per-point $REPETICIONES ejercicio-2-mezcla-k
./MainGraph.sh --xlabel "Número de vectores" --ylabel "Tiempo (en milisegundos)" --min-x 250 --max-x 10000 --num-points 39  --repetitions-per-point $REPETICIONES ejercicio-2-mezcla-k
rm ejercicio-2-mezcla-k

# GRUPO 6
g++ -O1 src/ejercicio-1-comp-fija-no-repetidos-hacked.cpp -o ejercicio-1-comp-fija-no-repetidos-comparado-hacked
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en nanosegundos)" --min-x 1 --max-x 21 --num-points 10  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-no-repetidos-comparado-hacked
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en nanosegundos)" --min-x 25 --max-x 1000 --num-points 39  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-no-repetidos-comparado-hacked
rm ejercicio-1-comp-fija-no-repetidos-comparado-hacked

# GRUPO 7
g++ -O1 src/ejercicio-1-comp-fija-no-repetidos-hacked.cpp -D UMBRAL=50000000 -o ejercicio-1-comp-fija-busqueda-lineal
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en nanosegundos)" --min-x 1 --max-x 21 --num-points 10  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-busqueda-lineal
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en nanosegundos)" --min-x 250000 --max-x 10000000 --num-points 39  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-busqueda-lineal
rm ejercicio-1-comp-fija-busqueda-lineal

# GRUPO 8
g++ -D REPETITIONS=50 -D SIZE_VECTOR=2000 src/ejercicio-1-comp-fija-no-repetidos.cpp -o ejercicio-1-comp-fija-no-repetidos
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en nanosegundos)" --min-x 1 --max-x 2 --num-points 1  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-no-repetidos
./MainGraph.sh --xlabel "Número de componentes del vector" --ylabel "Tiempo (en nanosegundos)" --min-x 25 --max-x 1000 --num-points 39  --repetitions-per-point $REPETICIONES ejercicio-1-comp-fija-no-repetidos
rm ejercicio-1-comp-fija-no-repetidos

# Delete the scripts imported from ../GraphKiller.
rm {BestFitter,GraphPlotter,PointsPlotter,MainGraph,Regressions,TableGenerator}.sh

### END
