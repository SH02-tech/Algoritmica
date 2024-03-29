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
programs=('floyd.cpp')

# Arrays of data:
#	1. min
#	2. max
#	3. number of jumps
#	4. number of repeats

declare -a OrdenData
OrdenData=(50 45050 30 20)

declare -a FloydData
FloydData=(5 755 25 20)

declare -a HanoyData
HanoiData=(2 27 25 20)

# Copy the scripts from ../GraphKiller, so we have them in the current directory of GraphP1.sh
cp ../GraphKiller/*.sh .

for ((i=0; i<${#programs[@]}; ++i))
do	
	
	src_file=${programs[i]}
	output=${src_file%%.cpp}

	for j in 0 1 2 3
	do
		g++ -O$j "$SRC_PATH"/${programs[i]} -o "$output_$j"
	
		if [[ ${programs[i]} == "floyd.cpp" ]]
		then
			./MainGraph.sh  --xlabel "Número de nodos" --ylabel "Tiempo (en microsegundos)" \
					--min-x ${FloydData[0]} --max-x ${FloydData[1]} \
					--num-points ${FloydData[2]} --repetitions-per-point ${FloydData[3]} \
					"$output_$j"
			
		elif [[ ${programs[i]} == "hanoi.cpp" ]]
		then
			./MainGraph.sh  --xlabel "Número de discos" --ylabel "Tiempo (en microsegundos)" \
					--min-x ${HanoiData[0]} --max-x ${HanoiData[1]} \ 
					--num-points ${HanoiData[2]} --repetitions-per-point ${HanoiData[3]} \
					"$output_$j"
		else
			./MainGraph.sh  --xlabel "Número de componentes del vector" --ylabel "Tiempo (en microsegundos)" \
					--min-x ${OrdenData[0]} --max-x ${OrdenData[1]} \
					--num-points ${OrdenData[2]} --repetitions-per-point ${OrdenData[3]} \
					"$output_$j"
		fi
		
		rm "$output_$j"
	done
done

# Delete the scripts imported from ../GraphKiller.
rm {BestFitter,PointsPlotter,GraphPlotter,MainGraph,Regressions,TableGenerator}.sh

### END
