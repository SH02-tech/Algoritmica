#!/bin/bash

# ARGUMENTS table : regresion type : eje x (min max) : eje y (min max) : salida

gnuplot -persist <<-EOFMarker
    set title "Análisis $2"
    set xlabel "Número de elementos"
    set xrange [$3:$4]
    set ylabel "Tiempo"
    set yrange [$5:$6]
    set style data lines
    plot "$1" 

EOFMarker
