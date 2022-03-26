#!/bin/bash
######################################################################
# Archive: MainGraph.sh
# Parameters: the necessary parameters of the rest of the scripts:
#	1. .cpp
#	2. max (maximum amount of data) 
# 	3. min (minimum amount of data)
#	4. number of measures
#	5. name of the output file of TableGenerator.sh 
# 	6. name of the output file of Regressions.sh
#	7. name of the output file of the BestFitter.sh
#	8. name of the output file of the GraphPlotter.sh
# Returns: A directory called with the same name as the .cpp file 
# 	   with three files, the data table, the regressions info
#	   and the graphic.
######################################################################

cppNameDir=${1%%.*}

mkdir "$cppNameDir"

# Executing the first script: TableGenerator.sh
# It will obtain two files: $5.dat and $5.tex
./TableGenerator.sh $1 $2 $3 $4 $5  
# We move the $5.dat (data table) to the directory created
mv "$5.dat" $cppNameDir

# Executing the second script: Regressions.sh
# It will obtain one file: $6.txt
./Regressions.sh "$5.dat" $6
# We move the $6.txt (regressions info) to the directory created
mv "$6.txt" $cppNameDir

# Executing the third script: BestFitter.sh
# It will obtain one file: $7.txt 
./BestFitter.sh "$6.txt" $7

# Executing the fourth script: GraphPlotter.sh
# It will obtain one file: $8.pdf
./GraphPlotter "$7.txt" $8
# We move the $8.txt (graphic) to the directory created
mv "$8.pdf" $cppNameDir

##### END

