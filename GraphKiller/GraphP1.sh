######################################################################
# Archive: MainGraph.sh
# Parameters: the necessary parameters of the rest of the scripts:
#	1. .cpp
#	2. max (maximum amount of data) 
# 	3. min (minimum amount of data)
#	4. number of jumps
#	5. number of repeats
#	6. name of the output file of TableGenerator.sh 
# 	7. name of the output file of Regressions.sh
#	8. name of the output file of the BestFitter.sh
#	9. name of the output file of the GraphPlotter.sh
# Returns: A directory called with the same name as the .cpp file 
# 	   with three files, the data table, the regressions info
#	   and the graphic.
######################################################################

programs=('floyd.cpp' 'hanoi.cpp' 'heapsort.cpp' 'insercion.cpp' 'quicksort.cpp' 'seleccion.cpp')

OrdenData=(100000 100 15 20)
FloydData=(3500 5 15 20)
HanoyData=(2 24  )



for i in "${programs[@]}"
do	
	cppNameDir=${programs[i]%%.*}
	mkdir "$cppNameDir"
	nameFileTableGenerator="$ccpNameDir-table"		# Name of the output file of TableGenerator.sh 
	nameFileRegressions="$cppNameDir-regressions"		# Name of the output file of Regressions.sh
	nameFileBestFitter="$cppNameDir-bestFitter"		# Name of the output file of the BestFitter.sh
	nameFileGraphPlotter="$cppNameDir-graphPlotter"	# Name of the output file of the GraphPlotter.sh
	
	# Executing the first script: TableGenerator.sh
	# It will obtain two files: $nameFileTableGenerator.dat and $nameFileTableGenerator.tex

	if [ ${programs[i]} == "floyd.cpp" ]
	then
		./TableGenerator.sh ${programs[i]} ${FloydData[0]} ${FloydData[1]} ${FloydData[2]} ${FloydData[3]} $nameFileTableGenerator
		
	elif [ ${programs[i]} == "hanoi.cpp" ]
	then
		./TableGenerator.sh ${programs[i]} ${HanoyData[0]} ${HanoyData[1]} ${HanoyData[2]} ${HanoyData[3]} $nameFileTableGenerator
	else
		./TableGenerator.sh ${programs[i]} ${OrdenData[0]} ${OrdenData[1]} ${OrdenData[2]} ${OrdenData[3]} $nameFileTableGenerator
	fi
	
	# Executing the second script: Regressions.sh
	# It will obtain one file: $nameFileRegressions.txt
	./Regressions.sh "$nameFileTableGenerator.dat" $nameFileRegressions
	
	# Executing the third script: BestFitter.sh
	# It will obtain one file: $nameFileBestFitter.txt 
	./BestFitter.sh "$nameFileRegressions.txt" $nameFileBestFitter
	
	# Executing the fourth script: GraphPlotter.sh
	# It will obtain one file: $nameFileGraphPlotter.pdf
	./GraphPlotter "$nameFileBestFitter.txt" $nameFileGraphPlotter
	
	# Executing the fifth script: MainGraph.sh
	./MainGraph --xlabel --ylabel ${programs[i]} 
	
	
		
	
done







### END
cppNameDir=${1%%.*}


mkdir "$cppNameDir"

# Executing the first script: TableGenerator.sh
# It will obtain two files: $6.dat and $6.tex
./TableGenerator.sh $1 $2 $3 $4 $5 $6 
# We move the $6.dat (data table) to the directory created
mv "$6.dat" $cppNameDir

# Executing the second script: Regressions.sh
# It will obtain one file: $7.txt
./Regressions.sh "$6.dat" $7
# We move the $7.txt (regressions info) to the directory created
mv "$7.txt" $cppNameDir

# Executing the third script: BestFitter.sh
# It will obtain one file: $7.txt 
./BestFitter.sh "$7.txt" $8



# Executing the fourth script: GraphPlotter.sh
# It will obtain one file: $9.pdf
./GraphPlotter "$8.txt" $9
# We move the $8.txt (graphic) to the directory created
mv "$9.pdf" $cppNameDir

##### END
