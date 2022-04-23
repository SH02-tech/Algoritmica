#!/bin/bash
######################################################################
# Archive: MainGraph.sh
# It pass all the necessaru to the MainGraph
# Parameters: Not necessary
# Return: Nothing
######################################################################
SRC_PATH="src/"
OUTPUT="exe"

declare -a programs
programs=('ejercicio1.cpp')
#programs=('ejercicio1.cpp','ejercicio2.cpp')

# Arrays of data:
#	1. min
#	2. max
#	3. number of jumps
#	4. number of repeats

declare -a Data
OrdenData=(1 11 10 1)

# Copy the scripts from ../GraphKiller, so we have them in the current directory of GraphP1.sh
cp ../GraphKiller/*.sh .

for ((i=0; i<${#programs[@]}; ++i))
do	
	src_file=${programs[i]}
	output=${src_file%%.cpp}

	g++ -O3 "$SRC_PATH"/${programs[i]} -o $output

	./MainGraph.sh  --xlabel "Número de componentes del vector" --ylabel "Tiempo (en microsegundos)" \
			--min-x ${OrdenData[0]} --max-x ${OrdenData[1]} \
			--num-points ${OrdenData[2]} --repetitions-per-point ${OrdenData[3]} \
			$output
	rm $output
done

# Delete the scripts imported from ../GraphKiller.
rm {BestFitter,GraphPlotter,PointsPlotter,MainGraph,Regressions,TableGenerator}.sh

### END
