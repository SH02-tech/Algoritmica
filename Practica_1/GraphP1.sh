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
programs=('heapsort.cpp' 'quicksort.cpp' 'seleccion.cpp' 'hanoi.cpp' 'insercion.cpp' 'floyd.cpp')
# programs=('seleccion.cpp')

# Arrays of data:
#	1. min
#	2. max
#	3. number of jumps
#	4. number of repeats

declare -a OrdenData
OrdenData=(50 45050 30 20)

declare -a FloydData
FloydData=(5 755 25 20)

declare -a HanoiData
HanoiData=(2 27 20 5)

# Copy the scripts from ../GraphKiller, so we have them in the current directory of GraphP1.sh
cp ../GraphKiller/*.sh .

for ((i=0; i<${#programs[@]}; ++i))
do	
	src_file=${programs[i]}
	output=${src_file%%.cpp}

	g++ -O3 "$SRC_PATH"/${programs[i]} -o $output
	
	if [[ ${programs[i]} == "floyd.cpp" ]]
	then
		./MainGraph.sh  --xlabel "Número de nodos" --ylabel "Tiempo (en microsegundos)" \
				--min-x ${FloydData[0]} --max-x ${FloydData[1]} \
				--num-points ${FloydData[2]} --repetitions-per-point ${FloydData[3]} \
				$output
		
	elif [[ ${programs[i]} == "hanoi.cpp" ]]
	then
		./MainGraph.sh  --xlabel "Número de discos" --ylabel "Tiempo (en microsegundos)" \
				--min-x ${HanoiData[0]} --max-x ${HanoiData[1]} \
				--num-points ${HanoiData[2]} --repetitions-per-point ${HanoiData[3]} \
				$output
	else
		./MainGraph.sh  --xlabel "Número de componentes del vector" --ylabel "Tiempo (en microsegundos)" \
				--min-x ${OrdenData[0]} --max-x ${OrdenData[1]} \
				--num-points ${OrdenData[2]} --repetitions-per-point ${OrdenData[3]} \
				$output
	fi
	
	rm $output
done

# Delete the scripts imported from ../GraphKiller.
rm {BestFitter,GraphPlotter,PointsPlotter,MainGraph,Regressions,TableGenerator}.sh

### END
