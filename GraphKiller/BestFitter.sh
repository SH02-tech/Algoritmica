#!/bin/bash
#######################################################################
# Archive: BestFitter.sh
# Input:
# 1. Archive with the information of all the regresions obtain in 
#    Regresions.ss, including the fit function, the parameters of the 
#    function and the ERM.
# Output:
# 1. Archieve that contais the information of the best type of adjust.
#######################################################################

# Obtain the ERM separated with \n


# Now, we have to determinate which is the maximum value

maxERM=-1

cut -d ' ' -f 3 $1 | cut -d ":" -f 2 | while IFS= read -r line 
do
	echo "Linea leída: $line"
	if [ $line > $maxERM ];
	then
		maxERM=$line;
	fi;
done

echo "The biggest number is: $maxERM"
