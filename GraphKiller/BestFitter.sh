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

FILENAME=$1
OUTPUT=$2

# Now, we have to determinate which is the maximum value

min_rms="10^99"
min_line=""

while read line
do 
	data=$(echo $line | grep -Eo "RMS:.*")
	arr_rms=(${data//:/ })
	
	rms=$(sed -E 's/([+-]?[0-9.]+)[eE]\+?(-?)([0-9]+)/(\1*10^\2\3)/g' <<< ${arr_rms[1]})
	
	if (( $(echo "$rms < $min_rms" | bc -l) ))
	then
		min_rms="$rms"
		min_line="$line"
	fi
	
done < $FILENAME

echo "$min_line" > $OUTPUT
