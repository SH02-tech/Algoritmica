#!/bin/bash

# ARGUMENTS table : regresion : título : eje x (label:min:max) : eje y label : salida 

table=$1
regresion=`cat "$2" | cut -d ":" -f 3 | awk '{ print substr($0, 6, length($0) - 8) }' `
title=$3
label_x=$4
min_x=$5
max_x=$6
label_y=$7
pdf=$8

gnuplot -persist <<-EOFMarker
    set title "Analysis $title"
    set xlabel "$label_x"
    set xrange [$min_x:$max_x]
    set ylabel"$label_y"
    set terminal pdf
    set output "$pdf"
    plot "$table" with linespoints , $regresion with linespoints

EOFMarker
