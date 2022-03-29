#!/bin/bash

# ARGUMENTS table : título : eje x (label:min:max) : eje y label : salida 

table=$1
title=$2
label_x=$3
min_x=$4
max_x=$5
label_y=$6
pdf=$7

gnuplot -persist <<-EOFMarker
	unset key
    set title "$title"
    set xlabel "$label_x"
    set xrange [$min_x:$max_x]
    set ylabel "$label_y"
    set terminal pdf
    set output "$pdf"
    plot "$table"

EOFMarker

