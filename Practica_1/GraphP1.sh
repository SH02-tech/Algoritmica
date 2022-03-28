######################################################################
# Archive: MainGraph.sh
# It pass all the necessaru to the MainGraph
# Parameters: Not necessary
# Return: Nothing
######################################################################

programs=('floyd.cpp' 'hanoi.cpp' 'heapsort.cpp' 'insercion.cpp' 'quicksort.cpp' 'seleccion.cpp')

# Arrays of data:
#	1. min
#	2. max
#	3. number of jumps
#	4. number of repeats
OrdenData=(100 100000 15 20)
FloydData=(5 3500 15 20)
HanoyData=(2 24 15 20)

# Copy the scripts from ../GraphKiller, so we have them in the current directory of GraphP1.sh
cp ../GraphKiller/* ./

for i in "${programs[@]}"
do	
	if [ ${programs[i]} == "floyd.cpp" ]
	then
		./MainGraph.sh  --xlabel "Number of nodes" --ylabel "time (seconds)" \
				--min-x ${FloydData[0]} --max-x ${FloydData[1]} \
				--num-points ${FloydData[2]} --repetitions-per-point ${FloydData[3]} \
				${programs[i]}
		
	elif [ ${programs[i]} == "hanoi.cpp" ]
	then
		./MainGraph.sh  --xlabel "Number of discs" --ylabel "time (seconds)" \
				--min-x ${FloydData[0]} --max-x ${FloydData[1]} \ 
				--num-points ${FloydData[2]} --repetitions-per-point ${FloydData[3]} \
				${programs[i]}
	else
		./MainGraph.sh  --xlabel "Number of components" --ylabel "time (seconds)" \
				--min-x ${FloydData[0]} --max-x ${FloydData[1]} \
				--num-points ${FloydData[2]} --repetitions-per-point ${FloydData[3]} \
				${programs[i]}
	fi
done

# Delete the scripts imported from ../GraphKiller.
rm ./floyd.sh
rm ./hanoi.sh
rm ./heapsort.sh
rm ./insercion.sh
rm ./quicksort.sh
rm ./seleccion.sh


### END
