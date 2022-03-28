#!/bin/bash

# ARGUMENTS: program min max nºjumps repeats nombre

ini=`bc <<< "scale=4; $2"` 
fin=`bc <<< "scale=4; $3"` 
jump=`bc <<< "scale=4; ($fin-$ini)/$4"` 
repeats=$5
nombre="$6.dat"
sum=0

while (( $(echo "$ini < $fin" |bc -l) ))
do
	sum=0
	
	for (( j=0; j<$repeats;j++ ))
	do
	  s=`./$1 $ini`
	  sum=$(echo $sum + $s | bc)
	done

	med=`bc <<< "scale=7; $sum/$repeats"`  
	lim=1
	
	if (( $(echo "$med < $lim" |bc -l) ));
	then
		media="0$med"
	else 
		media=$med
	fi

	echo "$ini $media" >> $nombre
	
	ini=`bc <<< "scale=4; $ini+$jump"`
done
